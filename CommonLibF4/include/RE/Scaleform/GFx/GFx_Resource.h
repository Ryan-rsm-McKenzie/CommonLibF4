#pragma once

#include "RE/Scaleform/Kernel/SF_Atomic.h"
#include "RE/Scaleform/Kernel/SF_Memory.h"
#include "RE/Scaleform/Kernel/SF_RefCount.h"

namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class Resource;
			class ResourceReport;

			class ResourceId
			{
			public:
				inline ~ResourceId() noexcept {}  // intentional

				std::uint32_t id;  // 00
			};
			static_assert(sizeof(ResourceId) == 0x4);

			class FileTypeConstants
			{
			public:
				enum class FileFormatType : std::int32_t
				{
					kUnopened,
					kUnknown,

					kSWF,
					kGFX,

					kJPEG = 10,
					kPNG = 11,
					kGIF = 12,
					kTGA = 13,
					kDDS = 14,
					kHDR = 15,
					kBMP = 16,
					kDIB = 17,
					kPFM = 18,
					kTIFF = 19,

					kWAVE = 20,

					kPVR = 21,
					kETC = 22,
					kSIF = 23,
					kGXT = 24,
					kGTX = 25,

					kNextAvail,
					kMultiFormat = 0xFFFF - 1,
					kOriginal = 0xFFFF
				};
			};
			static_assert(std::is_empty_v<FileTypeConstants>);

			class ResourceKey
			{
			public:
				using KeyHandle = void*;

				enum class KeyType : std::int32_t
				{
					kNone,
					kUnique,
					kFile,
					kGradient,
					kSubImage
				};

				class KeyInterface
				{
				public:
					virtual ~KeyInterface() = default;	// 00

					// add
					virtual void AddRef(KeyHandle a_data) = 0;								   // 01
					virtual void Release(KeyHandle a_data) = 0;								   // 02
					virtual KeyType GetKeyType(KeyHandle a_data) const = 0;					   // 03
					virtual std::size_t GetHashCode(KeyHandle a_data) const = 0;			   // 04
					virtual bool KeyEquals(KeyHandle a_data, const ResourceKey& a_other) = 0;  // 05
					virtual const char* GetFileURL(KeyHandle) const { return nullptr; }		   // 06
				};
				static_assert(sizeof(KeyInterface) == 0x8);

				// members
				KeyInterface* keyInterface;	 // 00
				KeyHandle keyData;			 // 08
			};
			static_assert(sizeof(ResourceKey) == 0x10);

			class ResourceLibBase :
				public RefCountBase<ResourceLibBase, 2>	 // 00
			{
			public:
				// add
				virtual void RemoveResourceOnRelease(Resource* a_res) = 0;	// 01
				virtual void PinResource(Resource* a_res) = 0;				// 02
				virtual void UnpinResource(Resource* a_res) = 0;			// 03
			};
			static_assert(sizeof(ResourceLibBase) == 0x10);

			class Resource :
				public NewOverrideBase<2>  // 00
			{
			public:
				virtual ~Resource() = default;	// 00

				// add
				virtual ResourceKey GetKey();						// 01
				virtual std::uint32_t GetResourceTypeCode() const;	// 02
				virtual ResourceReport* GetResourceReport();		// 03

				inline void AddRef() { InterlockedExchangeAdd(std::addressof(refCount.value), 1); }

				inline void Release()
				{
					if (InterlockedDecrement(std::addressof(refCount.value)) == 0) {
						delete lib;
						lib = nullptr;
						delete this;
					}
				}

				// members
				AtomicInt<std::int32_t> refCount;  // 08
				ResourceLibBase* lib;			   // 10
			};
			static_assert(sizeof(Resource) == 0x18);
		}
	}
}