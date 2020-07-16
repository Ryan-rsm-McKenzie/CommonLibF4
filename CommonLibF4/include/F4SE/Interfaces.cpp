#include "F4SE/Interfaces.h"

#include "F4SE/API.h"

namespace F4SE
{
	bool MessagingInterface::RegisterListener(const char* a_sender, EventCallback* a_handler) const
	{
		return GetProxy().RegisterListener(GetPluginHandle(), a_sender, a_handler);
	}

	bool MessagingInterface::Dispatch(std::uint32_t a_messageType, void* a_data, std::uint32_t a_dataLen, const char* a_receiver) const
	{
		return GetProxy().Dispatch(GetPluginHandle(), a_messageType, a_data, a_dataLen, a_receiver);
	}

	void SerializationInterface::SetUniqueID(std::uint32_t a_uid)
	{
		return GetProxy().SetUniqueID(GetPluginHandle(), a_uid);
	}

	void SerializationInterface::SetRevertCallback(EventCallback* a_callback) const
	{
		return GetProxy().SetRevertCallback(GetPluginHandle(), a_callback);
	}

	void SerializationInterface::SetSaveCallback(EventCallback* a_callback) const
	{
		return GetProxy().SetSaveCallback(GetPluginHandle(), a_callback);
	}

	void SerializationInterface::SetLoadCallback(EventCallback* a_callback) const
	{
		return GetProxy().SetLoadCallback(GetPluginHandle(), a_callback);
	}

	void SerializationInterface::SetFormDeleteCallback(FormDeleteCallback* a_callback) const
	{
		return GetProxy().SetFormDeleteCallback(GetPluginHandle(), a_callback);
	}
}
