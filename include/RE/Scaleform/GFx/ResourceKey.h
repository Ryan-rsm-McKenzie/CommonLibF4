#pragma once


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			class ResourceKey
			{
			public:
				using KeyHandle = void*;


				enum class KeyType : UInt32
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
					virtual ~KeyInterface() = default;													// 00

					virtual void		AddRef(KeyHandle a_data) = 0;									// 01
					virtual void		Release(KeyHandle a_data) = 0;									// 02
					virtual KeyType		GetKeyType(KeyHandle a_data) const = 0;							// 03
					virtual UPInt		GetHashCode(KeyHandle a_data) const = 0;						// 04
					virtual bool		KeyEquals(KeyHandle a_data, const ResourceKey& a_other) = 0;	// 05
					virtual const char*	GetFileURL(KeyHandle a_data) const;								// 06
				};
				STATIC_ASSERT(sizeof(KeyInterface) == 0x8);


				class HashOp
				{
				public:
					UPInt operator()(const ResourceKey& a_key)
					{
						return a_key._keyInterface ? a_key._keyInterface->GetHashCode(a_key._keyData) : 0;
					}
				};
				STATIC_ASSERT(sizeof(HashOp) == 0x1);

			protected:
				KeyInterface*	_keyInterface;	// 00
				KeyHandle		_keyData;		// 08
			};
			STATIC_ASSERT(sizeof(ResourceKey) == 0x10);
		}
	}
}
