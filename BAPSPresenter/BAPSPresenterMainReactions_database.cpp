#include "stdafx.h"
#include "BAPSPresenterMain.h"

using namespace BAPSPresenter;

/** Just pass all the data through to the child form (if present) **/

void BAPSPresenterMain::addLibraryResult(u32int index, int dirtyStatus, System::String^ result)
{
	if (recordLibrarySearch != nullptr)
	{
		MethodInvokerObjObjStr^ mi = gcnew MethodInvokerObjObjStr(recordLibrarySearch, &RecordLibrarySearch::add);
		array<System::Object^>^ dd = gcnew array<System::Object^>(3) {(int)index, dirtyStatus, result};
		recordLibrarySearch->Invoke(mi,dd);
	}
}

void BAPSPresenterMain::setLibraryResultCount(int count)
{
	if (recordLibrarySearch != nullptr)
	{
		MethodInvokerObj^ mi = gcnew MethodInvokerObj(recordLibrarySearch, &RecordLibrarySearch::setResultCount);
		array<System::Object^>^ dd = gcnew array<System::Object^>(1) {count};
		recordLibrarySearch->Invoke(mi,dd);
	}
}

void BAPSPresenterMain::notifyLibraryError(int errorcode, System::String^ description)
{
	if (recordLibrarySearch != nullptr)
	{
		MethodInvokerObjStr^ mi = gcnew MethodInvokerObjStr(recordLibrarySearch, &RecordLibrarySearch::handleError);
		array<System::Object^>^ dd = gcnew array<System::Object^>(2) {errorcode, description};
		recordLibrarySearch->Invoke(mi,dd);
	}
}
void BAPSPresenterMain::addShowResult(u32int showid, System::String^ description)
{
	if (loadShowDialog != nullptr)
	{
		MethodInvokerObjStr^ mi = gcnew MethodInvokerObjStr(loadShowDialog, &LoadShowDialog::addShow);
		array<System::Object^>^ dd = gcnew array<System::Object^>(2) {(int)showid, description};
		loadShowDialog->Invoke(mi,dd);
	}
}

void BAPSPresenterMain::setShowResultCount(int count)
{
	if (loadShowDialog != nullptr)
	{
		MethodInvokerObj^ mi = gcnew MethodInvokerObj(loadShowDialog, &LoadShowDialog::setShowResultCount);
		array<System::Object^>^ dd = gcnew array<System::Object^>(1) {count};
		loadShowDialog->Invoke(mi,dd);
	}
}
void BAPSPresenterMain::addListingResult(u32int listingid, u32int channel, System::String^ description)
{
	if (loadShowDialog != nullptr)
	{
		MethodInvokerObjObjStr^ mi = gcnew MethodInvokerObjObjStr(loadShowDialog, &LoadShowDialog::addListing);
		array<System::Object^>^ dd = gcnew array<System::Object^>(3) {(int)listingid, (int)channel, description};
		loadShowDialog->Invoke(mi,dd);
	}
}
void BAPSPresenterMain::setListingResultCount(int count)
{
	if (loadShowDialog != nullptr)
	{
		MethodInvokerObj^ mi = gcnew MethodInvokerObj(loadShowDialog, &LoadShowDialog::setListingResultCount);
		array<System::Object^>^ dd = gcnew array<System::Object^>(1) {count};
		loadShowDialog->Invoke(mi,dd);
	}
}

void BAPSPresenterMain::notifyLoadShowError(int errorCode, System::String^ message)
{
	if (loadShowDialog != nullptr)
	{
		MethodInvokerObjStr^ mi = gcnew MethodInvokerObjStr(loadShowDialog, &LoadShowDialog::notifyError);
		array<System::Object^>^ dd = gcnew array<System::Object^>(2) {errorCode, message};
		loadShowDialog->Invoke(mi,dd);
	}
}