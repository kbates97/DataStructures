#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <fileapi.h>
#include <winuser.h>
#include <handleapi.h>
#include "GenericTree.h"
#include <string>
#include <fstream>

using std::wstring;
using std::wcout;
using std::endl;


bool ListDirectoryContents(const wchar_t *sDir, GenericTreeNode<wstring> * node);
void WriteTreeToFile(GenericTree<wstring>& tree);

int main()
{

	wchar_t* buffer = _wgetcwd(NULL, 0);
	GenericTree<wstring> tree;
	GenericTreeNode<wstring> root(buffer);
	tree.SetRoot(&root);
	ListDirectoryContents(buffer, tree.GetRoot());
	WriteTreeToFile(tree);
	return 0;
}

bool ListDirectoryContents(const wchar_t *sDir, GenericTreeNode<wstring> * node)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;

	wchar_t sPath[2048];

	//Specify a file mask. *.* = We want everything! 
	wsprintf(sPath, L"%s\\*.*", sDir);

	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Path not found: [%s]\n", sDir);
		return false;
	}

	do
	{
		//Find first file will always return "."
		//    and ".." as the first two directories. 
		if (wcscmp(fdFile.cFileName, L".") != 0
			&& wcscmp(fdFile.cFileName, L"..") != 0)
		{
			//Build up our file path using the passed in 
			//  [sDir] and the file/foldername we just found: 
			wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName);

			//Is the entity a File or Folder? 
			if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
			{
				node->AddChild(new GenericTreeNode<wstring>(sPath, node));
				ListDirectoryContents(sPath, node->GetChildren().back());
			}
			else {
				node->AddChild(new GenericTreeNode<wstring>(sPath, node));
			}
		}
	} while (FindNextFile(hFind, &fdFile)); //Find the next file. 

	FindClose(hFind); //Always, Always, clean things up! 

	return true;
}

void WriteTreeToFile(GenericTree<wstring>& tree)
{
	std::wofstream file;
	file.open("DirectoryTree.txt", std::ios::trunc);
	std::function<void(const GenericTreeNode<wstring> * const node)> visit = [&file] (const GenericTreeNode<wstring> * const node)
	{
		if (node->GetChildren().empty())
			file << L"File: " << node->GetData() << "\n";
		else
			file << L"Directory: " << node->GetData() << "\n";
	};
	tree.SetFunction(visit);
	tree.BreadthFirst();
	file.close();
}
