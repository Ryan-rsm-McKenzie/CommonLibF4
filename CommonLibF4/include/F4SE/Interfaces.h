#pragma once

#include "REL/Relocation.h"

#define F4SEAPI __cdecl

namespace RE
{
	namespace BSScript
	{
		class IVirtualMachine;
	}

	namespace GFx
	{
		class Movie;
		class Value;
	}
}

namespace F4SE
{
	using PluginHandle = std::uint32_t;

	class DelayFunctorManager;
	class ObjectRegistry;
	class PersistentObjectStorage;

	namespace detail
	{
		struct F4SEInterface
		{
			std::uint32_t f4seVersion;
			std::uint32_t runtimeVersion;
			std::uint32_t editorVersion;
			std::uint32_t isEditor;
			void*(F4SEAPI* QueryInterface)(std::uint32_t);
			std::uint32_t(F4SEAPI* GetPluginHandle)(void);
			std::uint32_t(F4SEAPI* GetReleaseIndex)(void);
		};

		struct F4SEMessagingInterface
		{
			std::uint32_t interfaceVersion;
			bool(F4SEAPI* RegisterListener)(std::uint32_t, const char*, void*);
			bool(F4SEAPI* Dispatch)(std::uint32_t, std::uint32_t, void*, std::uint32_t, const char*);
			void*(F4SEAPI* GetEventDispatcher)(std::uint32_t);
		};

		struct F4SEScaleformInterface
		{
			std::uint32_t interfaceVersion;
			bool(F4SEAPI* Register)(const char*, void*);
		};

		struct F4SESerializationInterface
		{
			std::uint32_t version;
			void(F4SEAPI* SetUniqueID)(std::uint32_t, std::uint32_t);
			void(F4SEAPI* SetRevertCallback)(std::uint32_t, void*);
			void(F4SEAPI* SetSaveCallback)(std::uint32_t, void*);
			void(F4SEAPI* SetLoadCallback)(std::uint32_t, void*);
			void(F4SEAPI* SetFormDeleteCallback)(std::uint32_t, void*);
			bool(F4SEAPI* WriteRecord)(std::uint32_t, std::uint32_t, const void*, std::uint32_t);
			bool(F4SEAPI* OpenRecord)(std::uint32_t, std::uint32_t);
			bool(F4SEAPI* WriteRecordData)(const void*, std::uint32_t);
			bool(F4SEAPI* GetNextRecordInfo)(std::uint32_t*, std::uint32_t*, std::uint32_t*);
			std::uint32_t(F4SEAPI* ReadRecordData)(void*, std::uint32_t);
			bool(F4SEAPI* ResolveHandle)(std::uint64_t, std::uint64_t*);
			bool(F4SEAPI* ResolveFormID)(std::uint32_t, std::uint32_t*);
		};

		struct F4SEPapyrusInterface
		{
			std::uint32_t interfaceVersion;
			bool(F4SEAPI* Register)(void*);
			void(F4SEAPI* GetExternalEventRegistrations)(const char*, void*, void*);
		};

		struct F4SETaskInterface
		{
			std::uint32_t interfaceVersion;
			void(F4SEAPI* AddTask)(void*);
			void(F4SEAPI* AddUITask)(void*);
		};

		struct F4SEObjectInterface
		{
			std::uint32_t interfaceVersion;
			DelayFunctorManager&(F4SEAPI* GetDelayFunctorManager)(void);
			ObjectRegistry&(F4SEAPI* GetObjectRegistry)(void);
			PersistentObjectStorage&(F4SEAPI* GetPersistentObjectStorage)(void);
		};
	}

	class QueryInterface
	{
	protected:
		[[nodiscard]] inline decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const detail::F4SEInterface&>(*this);
		}

	private:
		[[nodiscard]] constexpr REL::Version MakeVersion(std::uint32_t a_version) const noexcept
		{
			return {
				(a_version >> 8 * 3) & 0x0FF,
				(a_version >> 8 * 2) & 0x0FF,
				(a_version >> 8 / 2) & 0xFFF,
				(a_version >> 8 * 0) & 0x00F
			};
		}

	public:
		[[nodiscard]] inline REL::Version  EditorVersion() const noexcept { return MakeVersion(GetProxy().editorVersion); }
		[[nodiscard]] inline REL::Version  F4SEVersion() const noexcept { return MakeVersion(GetProxy().f4seVersion); }
		[[nodiscard]] inline PluginHandle  GetPluginHandle() const { return GetProxy().GetPluginHandle(); }
		[[nodiscard]] inline std::uint32_t GetReleaseIndex() const { return GetProxy().GetReleaseIndex(); }
		[[nodiscard]] inline bool		   IsEditor() const noexcept { return GetProxy().isEditor != 0; }
		[[nodiscard]] inline REL::Version  RuntimeVersion() const noexcept { return MakeVersion(GetProxy().runtimeVersion); }
	};

	class LoadInterface :
		public QueryInterface
	{
	public:
		enum : std::uint32_t
		{
			kInvalid = 0,
			kMessaging,
			kScaleform,
			kPapyrus,
			kSerialization,
			kTask,
			kObject
		};

		[[nodiscard]] inline void* QueryInterface(std::uint32_t a_id) const { return GetProxy().QueryInterface(a_id); }
	};

	class MessagingInterface
	{
	private:
		[[nodiscard]] inline decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const detail::F4SEMessagingInterface&>(*this);
		}

	public:
		enum : std::uint32_t
		{
			kVersion = 1
		};

		enum : std::uint32_t
		{
			kPostLoad,
			kPostPostLoad,
			kPreLoadGame,
			kPostLoadGame,
			kPreSaveGame,
			kPostSaveGame,
			kDeleteGame,
			kInputLoaded,
			kNewGame,
			kGameLoaded,
			kGameDataReady
		};

		struct Message
		{
			const char*	  sender;
			std::uint32_t type;
			std::uint32_t dataLen;
			void*		  data;
		};

		using EventCallback = void F4SEAPI(Message* a_msg);

		[[nodiscard]] inline std::uint32_t Version() const noexcept { return GetProxy().interfaceVersion; }

		bool RegisterListener(const char* a_sender, EventCallback* a_handler) const;
		bool Dispatch(std::uint32_t a_messageType, void* a_data, std::uint32_t a_dataLen, const char* a_receiver) const;

		[[nodiscard]] void* GetEventDispatcher(std::uint32_t a_dispatcherID) const
		{
			GetProxy().GetEventDispatcher(a_dispatcherID);
		}
	};

	class ScaleformInterface
	{
	private:
		[[nodiscard]] inline decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const detail::F4SEScaleformInterface&>(*this);
		}

	public:
		enum : std::uint32_t
		{
			kVersion = 1
		};

		using RegisterCallback = bool F4SEAPI(RE::GFx::Movie* a_view, RE::GFx::Value* a_value);

		[[nodiscard]] inline std::uint32_t Version() const noexcept { return GetProxy().interfaceVersion; }

		inline bool Register(const char* a_name, RegisterCallback* a_callback) const
		{
			return GetProxy().Register(a_name, a_callback);
		}
	};

	class SerializationInterface
	{
	private:
		[[nodiscard]] inline decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const detail::F4SESerializationInterface&>(*this);
		}

	public:
		enum : std::uint32_t
		{
			kVersion = 1,
		};

		using EventCallback = void		F4SEAPI(const SerializationInterface* a_intfc);
		using FormDeleteCallback = void F4SEAPI(std::uint64_t a_handle);

		[[nodiscard]] inline std::uint32_t Version() const noexcept { return GetProxy().version; }

		void SetUniqueID(std::uint32_t a_uid);
		void SetRevertCallback(EventCallback* a_callback) const;
		void SetSaveCallback(EventCallback* a_callback) const;
		void SetLoadCallback(EventCallback* a_callback) const;
		void SetFormDeleteCallback(FormDeleteCallback* a_callback) const;

		inline bool WriteRecord(std::uint32_t a_type, std::uint32_t a_version, const void* a_buf, std::uint32_t a_length) const
		{
			return GetProxy().WriteRecord(a_type, a_version, a_buf, a_length);
		}

		inline bool OpenRecord(std::uint32_t a_type, std::uint32_t a_version) const
		{
			return GetProxy().OpenRecord(a_type, a_version);
		}

		inline bool WriteRecordData(const void* a_buf, std::uint32_t a_length) const
		{
			return GetProxy().WriteRecordData(a_buf, a_length);
		}

		inline bool GetNextRecordInfo(std::uint32_t& a_type, std::uint32_t& a_version, std::uint32_t& a_length) const
		{
			return GetProxy().GetNextRecordInfo(
				std::addressof(a_type),
				std::addressof(a_version),
				std::addressof(a_length));
		}

		inline std::uint32_t ReadRecordData(void* a_buf, std::uint32_t a_length) const
		{
			return GetProxy().ReadRecordData(a_buf, a_length);
		}

		[[nodiscard]] inline std::optional<std::uint64_t> ResolveHandle(std::uint64_t a_handle) const
		{
			std::uint64_t result{ 0 };
			if (GetProxy().ResolveHandle(a_handle, std::addressof(result))) {
				return result;
			} else {
				return std::nullopt;
			}
		}

		[[nodiscard]] inline std::optional<std::uint32_t> ResolveFormID(std::uint32_t a_formID) const
		{
			std::uint32_t result{ 0 };
			if (GetProxy().ResolveFormID(a_formID, std::addressof(result))) {
				return result;
			} else {
				return std::nullopt;
			}
		}
	};

	class PapyrusInterface
	{
	private:
		[[nodiscard]] inline decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const detail::F4SEPapyrusInterface&>(*this);
		}

	public:
		enum : std::uint32_t
		{
			kVersion = 2
		};

		using RegisterFunctions = bool F4SEAPI(RE::BSScript::IVirtualMachine* a_vm);
		using RegistrantFunctor = void F4SEAPI(std::uint64_t a_handle, const char* a_scriptName, const char* a_callbackName, void* a_data);

		[[nodiscard]] inline std::uint32_t Version() const noexcept { return GetProxy().interfaceVersion; }

		inline bool Register(RegisterFunctions* a_callback) const { return GetProxy().Register(a_callback); }

		inline void GetExternalEventRegistrations(const char* a_eventName, void* a_data, RegistrantFunctor* a_functor) const
		{
			GetProxy().GetExternalEventRegistrations(a_eventName, a_data, a_functor);
		}
	};

	class ITaskDelegate
	{
	public:
		virtual ~ITaskDelegate() noexcept = default;
		virtual void Run() = 0;
	};

	class TaskInterface
	{
	private:
		[[nodiscard]] inline decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const detail::F4SETaskInterface&>(*this);
		}

		class TaskDelegate :
			public ITaskDelegate
		{
		public:
			inline TaskDelegate(std::function<void()> a_task) noexcept :
				_impl(std::move(a_task))
			{}

			inline void Run() override { _impl(); }

		private:
			std::function<void()> _impl;
		};

	public:
		enum
		{
			kVersion = 2
		};

		[[nodiscard]] inline std::uint32_t Version() const noexcept { return GetProxy().interfaceVersion; }

		inline void AddTask(ITaskDelegate* a_task) const { GetProxy().AddTask(a_task); }
		inline void AddTask(std::function<void()> a_task) const { AddTask(new TaskDelegate(std::move(a_task))); }
		inline void AddUITask(ITaskDelegate* a_task) const { GetProxy().AddUITask(a_task); }
		inline void AddUITask(std::function<void()> a_task) const { AddUITask(new TaskDelegate(std::move(a_task))); }
	};

	class ObjectInterface
	{
	private:
		[[nodiscard]] inline decltype(auto) GetProxy() const noexcept
		{
			return reinterpret_cast<const detail::F4SEObjectInterface&>(*this);
		}

	public:
		enum
		{
			kVersion = 1
		};

		[[nodiscard]] inline std::uint32_t	   Version() const noexcept { return GetProxy().interfaceVersion; }
		[[nodiscard]] DelayFunctorManager&	   GetDelayFunctorManager() const { return GetProxy().GetDelayFunctorManager(); }
		[[nodiscard]] ObjectRegistry&		   GetObjectRegistry() const { return GetProxy().GetObjectRegistry(); }
		[[nodiscard]] PersistentObjectStorage& GetPersistentObjectStorage() const { return GetProxy().GetPersistentObjectStorage(); }
	};

	struct PluginInfo
	{
		std::uint32_t infoVersion;
		const char*	  name;
		std::uint32_t version;
	};
}
