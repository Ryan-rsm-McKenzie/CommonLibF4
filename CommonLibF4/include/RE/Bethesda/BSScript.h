#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"

namespace RE
{
	namespace BSScript
	{
		namespace Internal
		{
			class VirtualMachine;
		}

		class ErrorLogger;
		class IComplexType;
		class Stack;
		class StackFrame;
		class Variable;

		class TypeInfo
		{
		public:
			enum class RawType : std::uint32_t;

			~TypeInfo() noexcept {}	 // intentional

			// members
			union
			{
				stl::enumeration<RawType, std::uint32_t> rawType;
				IComplexType* complexTypeInfo;
			} data;	 // 0
		};
		static_assert(sizeof(TypeInfo) == 0x8);

		class IComplexType :
			public BSIntrusiveRefCounted  // 08
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IComplexType };
			static constexpr auto VTABLE{ VTABLE::BSScript__IComplexType };

			virtual ~IComplexType() = 0;  // 00

			// add
			virtual TypeInfo::RawType GetRawType() const = 0;  // 01
		};
		static_assert(sizeof(IComplexType) == 0x10);

		class PropertyGroupInfo :
			public BSIntrusiveRefCounted  // 00
		{
		public:
			// members
			BSFixedString groupName;				// 08
			BSFixedString docString;				// 10
			std::uint32_t userFlags;				// 18
			BSTArray<BSFixedString> propertyNames;	// 20
		};
		static_assert(sizeof(PropertyGroupInfo) == 0x38);

		class ObjectTypeInfo :
			public IComplexType	 // 00
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__ObjectTypeInfo };
			static constexpr auto VTABLE{ VTABLE::BSScript__ObjectTypeInfo };

			// members
			BSFixedString name;											  // 10
			BSTSmartPointer<BSScript::ObjectTypeInfo> parentTypeInfo;	  // 18
			BSFixedString docString;									  // 20
			BSTArray<BSTSmartPointer<PropertyGroupInfo>> propertyGroups;  // 28
			std::uint32_t linkedValid : 2;								  // 40:00
			std::uint32_t isConst : 1;									  // 40:02
			std::uint32_t userFlagCount : 5;							  // 40:03
			std::uint32_t variableCount : 10;							  // 40:08
			std::uint32_t variableUserFlagCount : 6;					  // 40:18
			std::uint32_t initialValueCount : 10;						  // 44:00
			std::uint32_t propertyCount : 10;							  // 44:10
			std::uint32_t staticFunctionCount : 9;						  // 44:20
			std::uint32_t emptyStateMemberFunctionCount : 11;			  // 48:00
			std::uint32_t namedStateCount : 7;							  // 48:11
			std::uint32_t initialState : 7;								  // 48:18
			void* data;													  // 50
		};
		static_assert(sizeof(ObjectTypeInfo) == 0x58);

		namespace Internal
		{
			class VDescTable
			{
			public:
				// members
				BSTTuple<BSFixedString, BSScript::TypeInfo>* entries;  // 00
				std::uint16_t paramCount;							   // 08
				std::uint16_t totalEntries;							   // 0A
			};
			static_assert(sizeof(VDescTable) == 0x10);
		}

		class IFunction :
			public BSIntrusiveRefCounted  // 08
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IFunction };
			static constexpr auto VTABLE{ VTABLE::BSScript__IFunction };

			enum class CallResult
			{
				kCompleted,
				kSetupForVM,
				kInProgress,
				kFailedRetry,
				kFailedAbort
			};

			enum class FunctionType
			{
				kNormal,
				kPropertyGetter,
				kPropertySetter
			};

			virtual ~IFunction() = default;	 // 00

			// add
			virtual const BSFixedString& GetName() const = 0;																											   // 01
			virtual const BSFixedString& GetObjectTypeName() const = 0;																									   // 02
			virtual const BSFixedString& GetStateName() const = 0;																										   // 03
			virtual TypeInfo GetReturnType() const = 0;																													   // 04
			virtual std::uint32_t GetParamCount() const = 0;																											   // 05
			virtual void GetParam(std::uint32_t a_param, BSFixedString& a_aramName, TypeInfo& a_paramType) const = 0;													   // 06
			virtual std::uint32_t GetStackFrameSize() const = 0;																										   // 07
			virtual bool GetIsNative() const = 0;																														   // 08
			virtual bool GetIsStatic() const = 0;																														   // 09
			virtual bool GetIsEmpty() const = 0;																														   // 0A
			virtual FunctionType GetFunctionType() const = 0;																											   // 0B
			virtual std::uint32_t GetUserFlags() const = 0;																												   // 0C
			virtual const BSFixedString& GetDocString() const = 0;																										   // 0D
			virtual void InsertLocals(StackFrame& a_frame) const = 0;																									   // 0E
			virtual CallResult Call(const BSTSmartPointer<Stack>& a_stack, ErrorLogger& a_errorLogger, Internal::VirtualMachine& a_vm, bool a_inScriptTasklet) const = 0;  // 0F
			virtual const BSFixedString& GetSourceFilename() const = 0;																									   // 10
			virtual bool TranslateIPToLineNumber(std::uint32_t a_ip, std::uint32_t& a_lineNumber) const = 0;															   // 11
			virtual bool GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_variableName) const = 0;														   // 12
			virtual bool CanBeCalledFromTasklets() const = 0;																											   // 13
			virtual void SetCallableFromTasklets(bool a_taskletCallable) = 0;																							   // 14
		};
		static_assert(sizeof(IFunction) == 0x10);

		namespace NF_util
		{
			class NativeFunctionBase :
				public IFunction  // 00
			{
			public:
				static constexpr auto RTTI{ RTTI::BSScript__NF_util__NativeFunctionBase };
				static constexpr auto VTABLE{ VTABLE::BSScript__NF_util__NativeFunctionBase };

				// add
				virtual bool HasStub() const = 0;																																			// 15
				virtual bool MarshallAndDispatch(Variable& a_self, Internal::VirtualMachine& a_vm, std::uint32_t a_stackID, Variable& a_retVal, const StackFrame& a_stackFrame) const = 0;	// 16

				// members
				BSFixedString name;				 // 10
				BSFixedString objName;			 // 18
				BSFixedString stateName;		 // 20
				TypeInfo retType;				 // 28
				Internal::VDescTable descTable;	 // 30
				bool isStatic;					 // 40
				bool isCallableFromTasklet;		 // 41
				bool isLatent;					 // 42
				std::uint32_t userFlags;		 // 44
				BSFixedString docString;		 // 48
			};
			static_assert(sizeof(NativeFunctionBase) == 0x50);
		}
	}
}
