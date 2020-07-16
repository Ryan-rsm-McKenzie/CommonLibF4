#include "API.h"

#include "F4SE/Interfaces.h"

namespace F4SE
{
	namespace detail
	{
		struct APIStorage
		{
		public:
			[[nodiscard]] static APIStorage& get()
			{
				static APIStorage singleton;
				return singleton;
			}

			PluginHandle  pluginHandle{ static_cast<PluginHandle>(-1) };
			std::uint32_t releaseIndex{ 0 };

			MessagingInterface*		messagingInterface{ nullptr };
			ScaleformInterface*		scaleformInterface{ nullptr };
			PapyrusInterface*		papyrusInterface{ nullptr };
			SerializationInterface* serializationInterface{ nullptr };
			TaskInterface*			taskInterface{ nullptr };
			ObjectInterface*		objectInterface{ nullptr };

		private:
			APIStorage() = default;
			APIStorage(const APIStorage&) = delete;
			APIStorage(APIStorage&&) = delete;

			~APIStorage() noexcept = default;

			APIStorage& operator=(const APIStorage&) = delete;
			APIStorage& operator=(APIStorage&&) = delete;
		};
	}

	bool Init(const LoadInterface* a_intfc)
	{
		if (!a_intfc) {
			return false;
		}

		(void)REL::Module::get();
		(void)REL::IDDatabase::get();

		auto&		storage = detail::APIStorage::get();
		const auto& intfc = *a_intfc;

		storage.pluginHandle = intfc.GetPluginHandle();
		storage.releaseIndex = intfc.GetReleaseIndex();

		storage.messagingInterface = static_cast<MessagingInterface*>(intfc.QueryInterface(LoadInterface::kMessaging));
		storage.scaleformInterface = static_cast<ScaleformInterface*>(intfc.QueryInterface(LoadInterface::kScaleform));
		storage.papyrusInterface = static_cast<PapyrusInterface*>(intfc.QueryInterface(LoadInterface::kPapyrus));
		storage.serializationInterface = static_cast<SerializationInterface*>(intfc.QueryInterface(LoadInterface::kSerialization));
		storage.taskInterface = static_cast<TaskInterface*>(intfc.QueryInterface(LoadInterface::kTask));
		storage.objectInterface = static_cast<ObjectInterface*>(intfc.QueryInterface(LoadInterface::kObject));

		return true;
	}

	PluginHandle GetPluginHandle() noexcept
	{
		return detail::APIStorage::get().pluginHandle;
	}

	std::uint32_t GetReleaseIndex() noexcept
	{
		return detail::APIStorage::get().releaseIndex;
	}

	const MessagingInterface* GetMessagingInterface() noexcept
	{
		return detail::APIStorage::get().messagingInterface;
	}

	const ScaleformInterface* GetScaleformInterface() noexcept
	{
		return detail::APIStorage::get().scaleformInterface;
	}

	const PapyrusInterface* GetPapyrusInterface() noexcept
	{
		return detail::APIStorage::get().papyrusInterface;
	}

	const SerializationInterface* GetSerializationInterface() noexcept
	{
		return detail::APIStorage::get().serializationInterface;
	}

	const TaskInterface* GetTaskInterface() noexcept
	{
		return detail::APIStorage::get().taskInterface;
	}

	const ObjectInterface* GetObjectInterface() noexcept
	{
		return detail::APIStorage::get().objectInterface;
	}
}
