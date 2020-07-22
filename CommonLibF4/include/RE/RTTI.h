#pragma once

namespace RE
{
	class type_info;

	namespace RTTI
	{
		template <class T>
		class RVA
		{
		public:
			using value_type = T;
			using pointer = value_type*;
			using reference = value_type&;

			constexpr RVA() noexcept = default;

			constexpr RVA(std::uint32_t a_rva) noexcept :
				_rva(a_rva)
			{}

			[[nodiscard]] pointer get() const { return is_good() ? REL::Relocation<T*>(_rva).get() : nullptr; }
			[[nodiscard]] reference operator*() const { return *get(); }
			[[nodiscard]] pointer operator->() const { return get(); }
			[[nodiscard]] pointer operator[](std::ptrdiff_t a_idx) const { return get() + a_idx; }
			[[nodiscard]] explicit constexpr operator bool() const noexcept { return is_good(); }

		protected:
			[[nodiscard]] constexpr bool is_good() const noexcept { return _rva != 0; }

			// members
			std::uint32_t _rva{ 0 };  // 00
		};
		static_assert(sizeof(RVA<void*>) == 0x4);

		struct TypeDescriptor
		{
		public:
			// members
			type_info* typeInfo;  // 00
			void* spare;		  // 08
			char name[];		  // 10
		};
		static_assert(sizeof(TypeDescriptor) == 0x10);	// can be larger

		struct PMD
		{
		public:
			// members
			std::int32_t mDisp;	 // 0
			std::int32_t pDisp;	 // 4
			std::int32_t vDisp;	 // 8
		};
		static_assert(sizeof(PMD) == 0xC);

		struct BaseClassArray
		{
		public:
			enum class Attribute
			{
				kNone = 0
			};

			// members
			RVA<TypeDescriptor> typeDescriptor;						// 00
			std::uint32_t numContainedBases;						// 04
			PMD pmd;												// 08
			stl::enumeration<Attribute, std::uint32_t> attributes;	// 14
		};
		static_assert(sizeof(BaseClassArray) == 0x18);

		struct ClassHierarchyDescriptor
		{
		public:
			enum class Attribute
			{
				kNoInheritance = 0,
				kMultipleInheritance = 1 << 0,
				kVirtualInheritance = 1 << 1,
				kAmbiguousInheritance = 1 << 2
			};

			// members
			std::uint32_t signature;								// 00
			stl::enumeration<Attribute, std::uint32_t> attributes;	// 04
			std::uint32_t numBaseClasses;							// 08
			RVA<BaseClassArray> baseClassArray;						// 0C
		};
		static_assert(sizeof(ClassHierarchyDescriptor) == 0x10);

		struct CompleteObjectLocator
		{
		public:
			enum class Signature
			{
				x86 = 0,
				x64 = 1
			};

			// members
			stl::enumeration<Signature, std::uint32_t> signature;  // 00
			std::uint32_t offset;								   // 04
			std::uint32_t ctorDispOffset;						   // 08
			RVA<TypeDescriptor> typeDescriptor;					   // 0C
			RVA<ClassHierarchyDescriptor> classDescriptor;		   // 10
		};
		static_assert(sizeof(CompleteObjectLocator) == 0x14);

		struct BaseClassDescriptor
		{
		public:
			enum class Attribute
			{
				kNone = 0,
				kNotVisible = 1 << 0,
				kAmbiguous = 1 << 1,
				kPrivate = 1 << 2,
				kPrivateOrProtectedBase = 1 << 3,
				kVirtual = 1 << 4,
				kNonPolymorphic = 1 << 5,
				kHasHierarchyDescriptor = 1 << 6
			};

			// members
			RVA<TypeDescriptor> typeDescriptor;						// 00
			std::uint32_t numContainedBases;						// 04
			PMD pmd;												// 08
			stl::enumeration<Attribute, std::uint32_t> attributes;	// 14
		};
		static_assert(sizeof(BaseClassDescriptor) == 0x18);
	}
}
