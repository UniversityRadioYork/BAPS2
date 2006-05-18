#include "StdAfx.h"
#include "BAPSPresenterMain.h"
#include "Messages.h"

using namespace BAPSPresenter;

System::Void BAPSPresenterMain::Directory_MouseDown(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e)
{
	BAPSListBox^ lb =( dynamic_cast<BAPSListBox^>(sender));
	int folder = safe_cast<int>(lb->Tag);
	//Retrieve the item at the specified location within the ListBox.
	int index = lb->indexFromY(e->Y);

	// Starts a drag-and-drop operation.
	if(index >= 0) 
	{
		FolderTempStruct^ fts = gcnew FolderTempStruct(index, folder);
		System::Windows::Forms::DragDropEffects result;
		result = lb->DoDragDrop(fts, System::Windows::Forms::DragDropEffects::Copy);
	}
}