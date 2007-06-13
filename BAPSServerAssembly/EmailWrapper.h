#pragma once
/** Code obtained from codeproject... */

namespace BAPSServerAssembly
{
	/** http://www.codeproject.com/managedcpp/sendmailmc__.asp **/

	ref class EmailWrapper
	{
	public:
		static bool sendEmail(	System::String ^ body);
	};
};