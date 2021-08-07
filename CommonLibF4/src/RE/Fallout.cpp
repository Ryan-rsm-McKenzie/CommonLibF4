#include "RE/Fallout.h"

namespace RE
{
	namespace BSSpring
	{
		template struct SpringState<float>;
		static_assert(sizeof(SpringState<float>) == 0xC);

		template struct SpringState<NiPoint2>;
		static_assert(sizeof(SpringState<NiPoint2>) == 0x14);

		template struct SpringState<NiPoint3>;
		static_assert(sizeof(SpringState<NiPoint3>) == 0x1C);
	}

	namespace detail
	{
		template class BSFixedString<char, false>;
		static_assert(sizeof(BSFixedString<char, false>) == 0x8);

		template class BSFixedString<char, true>;
		static_assert(sizeof(BSFixedString<char, true>) == 0x8);

		template class BSFixedString<wchar_t, false>;
		static_assert(sizeof(BSFixedString<wchar_t, false>) == 0x8);

		template class BSFixedString<wchar_t, true>;
		static_assert(sizeof(BSFixedString<wchar_t, true>) == 0x8);
	}

	template struct BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy<AlchemyItem>;
	static_assert(std::is_empty_v<BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy<AlchemyItem>>);

	template struct BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy<TESForm>;
	static_assert(std::is_empty_v<BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy<TESForm>>);

	template struct BSAutoLockReadLockPolicy<BSReadWriteLock>;
	static_assert(std::is_empty_v<BSAutoLockReadLockPolicy<BSReadWriteLock>>);

	template struct BSAutoLockWriteLockPolicy<BSReadWriteLock>;
	static_assert(std::is_empty_v<BSAutoLockWriteLockPolicy<BSReadWriteLock>>);

	template struct BSAutoLockDefaultPolicy<BSSpinLock>;
	static_assert(std::is_empty_v<BSAutoLockDefaultPolicy<BSSpinLock>>);

	template class BSAutoLock<BSReadWriteLock, BSAutoLockReadLockPolicy>;
	static_assert(sizeof(BSAutoLock<BSReadWriteLock, BSAutoLockReadLockPolicy>) == 0x8);

	template class BSAutoLock<BSReadWriteLock, BSAutoLockWriteLockPolicy>;
	static_assert(sizeof(BSAutoLock<BSReadWriteLock, BSAutoLockWriteLockPolicy>) == 0x8);

	template class BSAutoLock<BSSpinLock, BSAutoLockDefaultPolicy>;
	static_assert(sizeof(BSAutoLock<BSSpinLock, BSAutoLockDefaultPolicy>) == 0x8);

	template struct BSCRC32<std::int8_t>;
	template struct BSCRC32<std::uint8_t>;
	template struct BSCRC32<std::int16_t>;
	template struct BSCRC32<std::uint16_t>;
	template struct BSCRC32<std::int32_t>;
	template struct BSCRC32<std::uint32_t>;
	template struct BSCRC32<std::int64_t>;
	template struct BSCRC32<std::uint64_t>;
	template struct BSCRC32<BSFixedString>;
	template struct BSCRC32<BSFixedStringCS>;
	template struct BSCRC32<BSFixedStringW>;
	template struct BSCRC32<BSFixedStringWCS>;

	template class BSPointerHandle<Actor>;
	static_assert(sizeof(BSPointerHandle<Actor>) == 0x4);

	template class BSPointerHandle<Projectile>;
	static_assert(sizeof(BSPointerHandle<Projectile>) == 0x4);

	template class BSPointerHandle<TESObjectREFR>;
	static_assert(sizeof(BSPointerHandle<TESObjectREFR>) == 0x4);

	template class BSPointerHandleManagerInterface<Actor>;
	static_assert(std::is_empty_v<BSPointerHandleManagerInterface<Actor>>);

	template class BSPointerHandleManagerInterface<Projectile>;
	static_assert(std::is_empty_v<BSPointerHandleManagerInterface<Projectile>>);

	template class BSPointerHandleManagerInterface<TESObjectREFR>;
	static_assert(std::is_empty_v<BSPointerHandleManagerInterface<TESObjectREFR>>);

	template class BSTAlignedHeapArrayAllocator<0x10>::Allocator;
	static_assert(sizeof(BSTAlignedHeapArrayAllocator<0x10>::Allocator) == 0x10);

	template class BSTAtomicValue<std::int32_t>;
	static_assert(sizeof(BSTAtomicValue<std::int32_t>) == 0x4);

	template class BSTAtomicValue<std::uint32_t>;
	static_assert(sizeof(BSTAtomicValue<std::uint32_t>) == 0x4);

	template class BSTAtomicValue<std::int64_t>;
	static_assert(sizeof(BSTAtomicValue<std::int64_t>) == 0x8);

	template class BSTAtomicValue<std::uint64_t>;
	static_assert(sizeof(BSTAtomicValue<std::uint64_t>) == 0x8);

	template class BSTDataBuffer<1>;
	static_assert(sizeof(BSTDataBuffer<1>) == 0x10);

	template class BSTDataBuffer<2>;
	static_assert(sizeof(BSTDataBuffer<2>) == 0x10);

	template class BSTInterpolator<float, EaseOutInterpolator, GetCurrentPositionFunctor>;
	static_assert(sizeof(BSTInterpolator<float, EaseOutInterpolator, GetCurrentPositionFunctor>) == 0x18);

	template class BSTPoint2<std::int8_t>;
	static_assert(sizeof(BSTPoint2<std::int8_t>) == 0x2);

	template class BSTPoint2<std::uint8_t>;
	static_assert(sizeof(BSTPoint2<std::uint8_t>) == 0x2);

	template class BSTPoint2<std::int16_t>;
	static_assert(sizeof(BSTPoint2<std::int16_t>) == 0x4);

	template class BSTPoint2<std::uint16_t>;
	static_assert(sizeof(BSTPoint2<std::uint16_t>) == 0x4);

	template class BSTPoint2<std::int32_t>;
	static_assert(sizeof(BSTPoint2<std::int32_t>) == 0x8);

	template class BSTPoint2<std::uint32_t>;
	static_assert(sizeof(BSTPoint2<std::uint32_t>) == 0x8);

	template class BSTPoint2<float>;
	static_assert(sizeof(BSTPoint2<float>) == 0x8);

	template class BSTPoint2<double>;
	static_assert(sizeof(BSTPoint2<double>) == 0x10);

	template class BSTPoint2Base<std::int8_t>;
	static_assert(sizeof(BSTPoint2Base<std::int8_t>) == 0x2);

	template class BSTPoint2Base<std::uint8_t>;
	static_assert(sizeof(BSTPoint2Base<std::uint8_t>) == 0x2);

	template class BSTPoint2Base<std::int16_t>;
	static_assert(sizeof(BSTPoint2Base<std::int16_t>) == 0x4);

	template class BSTPoint2Base<std::uint16_t>;
	static_assert(sizeof(BSTPoint2Base<std::uint16_t>) == 0x4);

	template class BSTPoint2Base<std::int32_t>;
	static_assert(sizeof(BSTPoint2Base<std::int32_t>) == 0x8);

	template class BSTPoint2Base<std::uint32_t>;
	static_assert(sizeof(BSTPoint2Base<std::uint32_t>) == 0x8);

	template class BSTPoint2Base<float>;
	static_assert(sizeof(BSTPoint2Base<float>) == 0x8);

	template class BSTPoint2Base<double>;
	static_assert(sizeof(BSTPoint2Base<double>) == 0x10);

	template class BSTPoint3<std::int8_t>;
	static_assert(sizeof(BSTPoint3<std::int8_t>) == 0x3);

	template class BSTPoint3<std::uint8_t>;
	static_assert(sizeof(BSTPoint3<std::uint8_t>) == 0x3);

	template class BSTPoint3<std::int16_t>;
	static_assert(sizeof(BSTPoint3<std::int16_t>) == 0x6);

	template class BSTPoint3<std::uint16_t>;
	static_assert(sizeof(BSTPoint3<std::uint16_t>) == 0x6);

	template class BSTPoint3<std::int32_t>;
	static_assert(sizeof(BSTPoint3<std::int32_t>) == 0xC);

	template class BSTPoint3<std::uint32_t>;
	static_assert(sizeof(BSTPoint3<std::uint32_t>) == 0xC);

	template class BSTPoint3<float>;
	static_assert(sizeof(BSTPoint3<float>) == 0xC);

	template class BSTPoint3<double>;
	static_assert(sizeof(BSTPoint3<double>) == 0x18);

	template class BSTPoint3Base<std::int8_t>;
	static_assert(sizeof(BSTPoint3Base<std::int8_t>) == 0x3);

	template class BSTPoint3Base<std::uint8_t>;
	static_assert(sizeof(BSTPoint3Base<std::uint8_t>) == 0x3);

	template class BSTPoint3Base<std::int16_t>;
	static_assert(sizeof(BSTPoint3Base<std::int16_t>) == 0x6);

	template class BSTPoint3Base<std::uint16_t>;
	static_assert(sizeof(BSTPoint3Base<std::uint16_t>) == 0x6);

	template class BSTPoint3Base<std::int32_t>;
	static_assert(sizeof(BSTPoint3Base<std::int32_t>) == 0xC);

	template class BSTPoint3Base<std::uint32_t>;
	static_assert(sizeof(BSTPoint3Base<std::uint32_t>) == 0xC);

	template class BSTPoint3Base<float>;
	static_assert(sizeof(BSTPoint3Base<float>) == 0xC);

	template class BSTPoint3Base<double>;
	static_assert(sizeof(BSTPoint3Base<double>) == 0x18);

	template class BSTPointDefaultOps<std::int8_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::int8_t>>);

	template class BSTPointDefaultOps<std::uint8_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::uint8_t>>);

	template class BSTPointDefaultOps<std::int16_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::int16_t>>);

	template class BSTPointDefaultOps<std::uint16_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::uint16_t>>);

	template class BSTPointDefaultOps<std::int32_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::int32_t>>);

	template class BSTPointDefaultOps<std::uint32_t>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<std::uint32_t>>);

	template class BSTPointDefaultOps<float>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<float>>);

	template class BSTPointDefaultOps<double>;
	static_assert(std::is_empty_v<BSTPointDefaultOps<double>>);

	template class BSUntypedPointerHandle<>;
	static_assert(sizeof(BSUntypedPointerHandle<>) == 0x4);

	template class GetCurrentPositionFunctor<float>;
	static_assert(std::is_empty_v<GetCurrentPositionFunctor<float>>);

	template CharacterEvent* InputEvent::As() noexcept;
	template const CharacterEvent* InputEvent::As() const noexcept;

	template DeviceConnectEvent* InputEvent::As() noexcept;
	template const DeviceConnectEvent* InputEvent::As() const noexcept;

	template IDEvent* InputEvent::As<IDEvent>();
	template const IDEvent* InputEvent::As<IDEvent>() const;

	template ButtonEvent* InputEvent::As() noexcept;
	template const ButtonEvent* InputEvent::As() const noexcept;

	template CursorMoveEvent* InputEvent::As() noexcept;
	template const CursorMoveEvent* InputEvent::As() const noexcept;

	template KinectEvent* InputEvent::As() noexcept;
	template const KinectEvent* InputEvent::As() const noexcept;

	template MouseMoveEvent* InputEvent::As() noexcept;
	template const MouseMoveEvent* InputEvent::As() const noexcept;

	template ThumbstickEvent* InputEvent::As() noexcept;
	template const ThumbstickEvent* InputEvent::As() const noexcept;

	template class SettingT<GameSettingCollection>;
	static_assert(sizeof(SettingT<GameSettingCollection>) == 0x18);

	template class SettingT<INIPrefSettingCollection>;
	static_assert(sizeof(SettingT<INIPrefSettingCollection>) == 0x18);

	template class SettingT<INISettingCollection>;
	static_assert(sizeof(SettingT<INISettingCollection>) == 0x18);

	template class SettingT<LipSynchroSettingCollection>;
	static_assert(sizeof(SettingT<LipSynchroSettingCollection>) == 0x18);

	template class SettingT<RegSettingCollection>;
	static_assert(sizeof(SettingT<RegSettingCollection>) == 0x18);

	template class SettingCollection<Setting>;
	static_assert(sizeof(SettingCollection<Setting>) == 0x118);

	template class SettingCollectionList<Setting>;
	static_assert(sizeof(SettingCollectionList<Setting>) == 0x128);

	template class SettingCollectionMap<Setting>;
	static_assert(sizeof(SettingCollectionMap<Setting>) == 0x138);
}
