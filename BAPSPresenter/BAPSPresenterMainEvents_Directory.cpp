#include "StdAfx.h"
#include "BAPSPresenterMain.h"
#include "Messages.h"

using namespace BAPSPresenter;

System::Void BAPSPresenterMain::Directory_MouseDown(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e)
{
	System::Windows::Forms::ListBox^ lb =( dynamic_cast<System::Windows::Forms::ListBox^>(sender));
	int folder = safe_cast<int>(lb->Tag);
	//Retrieve the item at the specified location within the ListBox.
	int index = lb->SelectedIndex;

	// Starts a drag-and-drop operation.
	if(index >= 0) 
	{
		FolderTempStruct^ fts = gcnew FolderTempStruct(index, folder);
		System::Windows::Forms::DragDropEffects result;
		result = lb->DoDragDrop(fts, System::Windows::Forms::DragDropEffects::Copy);
	}
}