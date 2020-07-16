#pragma once

namespace F4SE
{
	using PluginHandle = std::uint32_t;

	class LoadInterface;

	class MessagingInterface;
	class ScaleformInterface;
	class PapyrusInterface;
	class SerializationInterface;
	class TaskInterface;
	class ObjectInterface;

	[[nodiscard]] bool Init(const LoadInterface* a_intfc);

	[[nodiscard]] PluginHandle	GetPluginHandle() noexcept;
	[[nodiscard]] std::uint32_t GetReleaseIndex() noexcept;

	[[nodiscard]] const MessagingInterface*		GetMessagingInterface() noexcept;
	[[nodiscard]] const ScaleformInterface*		GetScaleformInterface() noexcept;
	[[nodiscard]] const PapyrusInterface*		GetPapyrusInterface() noexcept;
	[[nodiscard]] const SerializationInterface* GetSerializationInterface() noexcept;
	[[nodiscard]] const TaskInterface*			GetTaskInterface() noexcept;
	[[nodiscard]] const ObjectInterface*		GetObjectInterface() noexcept;
}
