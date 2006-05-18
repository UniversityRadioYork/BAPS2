#pragma once

#include "ConfigOptions.h"

namespace BAPSPresenter
{
	delegate void UpdateDelegate();
	/**
		This stores all the info there is about a given option in hashtable
	**/
	ref struct OptionCacheInfo
	{
		int optionid;
		int type;
		bool isIndexed;
		System::String^ description;
		int intValue;
		System::String^ strValue;
		System::Collections::Hashtable^ valueList;
		System::Collections::Hashtable^ choiceList;
	};

	/** The config cache is designed as a quick access to config variables,
		You tell it what config item is expected next and then ask for that
		option from the server. It will then associate the result with the
		name you asked for.
	**/
	ref class ConfigCache
	{
	public:
		/** This is a static class so initialize all the static members **/
		static void initConfigCache()
		{
			descLookup = gcnew System::Collections::Hashtable();
			idLookup = gcnew System::Collections::Hashtable();
		}
		/** Nothing to destroy really **/
		static void closeConfigCache()
		{}
		/** add an option **/
		static void addOptionDescription(int optionid, int type, System::String^ description, bool isIndexed)
		{
			if (descLookup[description] == nullptr)
			{
				/** Make a new option info object **/
				OptionCacheInfo^ oci = gcnew OptionCacheInfo();
				/** Set all the info **/
				oci->optionid = optionid;
				oci->type = type;
				oci->description = description;
				oci->isIndexed = isIndexed;
				if (isIndexed)
				{
					/** for indexed options we need a hashtable of values **/
					oci->valueList = gcnew System::Collections::Hashtable();
				}
				if (oci->type == CONFIG_TYPE_CHOICE)
				{
					/** for choice based options we need a hashtable for the choices **/
					oci->choiceList = gcnew System::Collections::Hashtable();
				}
				/** place the option in the description hashtable **/
				descLookup[description]=oci;
				/** also place it in the optionid indexed hashtable so the 
					results can be added without hassle
				**/
				idLookup[optionid] = oci;
			}
		}
		static void addOptionChoice(int optionid, int choiceid, System::String^ description)
		{
			/** Make sure we know about the option this data refers to **/
			if (idLookup[optionid] != nullptr)
			{
				/** enter the setting in the hashtable **/
				static_cast<OptionCacheInfo^>(idLookup[optionid])->choiceList[description] = choiceid;
			}
		}
		static int findChoiceIndexFor(System::String^ optionDesc, System::String^ description)
		{
			if (descLookup[optionDesc] != nullptr)
			{
				/** fetch the id from the choice hashtable **/
				return safe_cast<int>(static_cast<OptionCacheInfo^>(descLookup[optionDesc])->choiceList[description]);
			}
			else
			{
				return -1;
			}
		}
		static void addOptionValue(int optionid, int index, System::String^ value)
		{
			/** Make sure we know about the option this data refers to **/
			if (idLookup[optionid] != nullptr)
			{
				if (index == -1)
				{
					/** Non indexed setting **/
					static_cast<OptionCacheInfo^>(idLookup[optionid])->strValue = value;
				}
				else
				{
					/** enter the setting in the hashtable **/
					static_cast<OptionCacheInfo^>(idLookup[optionid])->valueList[index] = value;
				}
			}
		}

		static void addOptionValue(int optionid, int index, int value)
		{
			/** Make sure we know azbout the option this data refers to **/
			if (idLookup[optionid] != nullptr)
			{
				if (index == -1)
				{
					/** Non indexed setting **/
					static_cast<OptionCacheInfo^>(idLookup[optionid])->intValue = value;
				}
				else
				{
					/** enter the setting in the hashtable **/
					static_cast<OptionCacheInfo^>(idLookup[optionid])->valueList[index] = value;
				}
			}
		}
		static OptionCacheInfo^ getOption(System::String^ optionDescription)
		{
			/** Gets an int from the cache **/
			if (descLookup[optionDescription] != nullptr)
			{
				return static_cast<OptionCacheInfo^>(descLookup[optionDescription]);
			}
			else
			{
				return nullptr;
			}
		}
		static int getValueInt(System::String^ optionDescription)
		{
			/** Gets an int from the cache **/
			if (descLookup[optionDescription] != nullptr)
			{
				return static_cast<OptionCacheInfo^>(descLookup[optionDescription])->intValue;
			}
			else
			{
				return 0;
			}
		}
		static int getValueInt(System::String^ optionDescription, int index)
		{
			/** Gets an int from the cache **/
			if (descLookup[optionDescription] != nullptr)
			{
				return safe_cast<int>(static_cast<OptionCacheInfo^>(descLookup[optionDescription])->valueList[index]);
			}
			else
			{
				return 0;
			}
		}
		static System::String^ getValueStr(System::String^ optionDescription)
		{
			/** Gets an int from the cache **/
			if (descLookup[optionDescription] != nullptr)
			{
				return static_cast<OptionCacheInfo^>(descLookup[optionDescription])->strValue;
			}
			else
			{
				return "";
			}
		}
		static System::String^ getValueStr(System::String^ optionDescription, int index)
		{
			/** Gets an int from the cache **/
			if (descLookup[optionDescription] != nullptr)
			{
				return safe_cast<System::String^>(static_cast<OptionCacheInfo^>(descLookup[optionDescription])->valueList[index]);
			}
			else
			{
				return "";
			}
		}
	private:
		static System::Collections::Hashtable^ descLookup;
		static System::Collections::Hashtable^ idLookup;
	};
};