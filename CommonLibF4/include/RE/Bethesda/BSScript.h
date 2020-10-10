#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTObjectArena.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"

namespace RE
{
	template <class F>
	using BSTThreadScrapFunction = msvc::function<F>;

	namespace BSScript
	{
		namespace Internal
		{
			class VirtualMachine;
		}

		class Array;
		class BoundScript;
		class ErrorLogger;
		class ICachedErrorMessage;
		class IComplexType;
		class IFunction;
		class ISavePatcherInterface;
		class IStackCallbackFunctor;
		class ITypeLinkedCallback;
		class JobList;
		class Object;
		class ObjectBindPolicy;
		class ObjectTypeInfo;
		class Stack;
		class StackFrame;
		class Struct;
		class StructTypeInfo;
		class Variable;

		struct ILoader;
		struct IObjectHandlePolicy;
		struct LogEvent;
		struct StatsEvent;

		class __declspec(novtable) ICachedErrorMessage
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__ICachedErrorMessage };
			static constexpr auto VTABLE{ VTABLE::BSScript__ICachedErrorMessage };

			virtual ~ICachedErrorMessage() = default;  // 00

			// add
			virtual void GetErrorMsg(BSFixedString& a_message) const = 0;  // 01
		};
		static_assert(sizeof(ICachedErrorMessage) == 0x8);

		class __declspec(novtable) ErrorLogger :
			public BSTEventSource<LogEvent>	 // 08
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__ErrorLogger };
			static constexpr auto VTABLE{ VTABLE::BSScript__ErrorLogger };

			enum class Severity
			{
				kInfo,
				kWarning,
				kError,
				kFatal
			};

			struct PerThreadErrorCounts
			{
			public:
				// members
				std::uint32_t fatalCount;	 // 0
				std::uint32_t errorCount;	 // 4
				std::uint32_t warningCount;	 // 8
			};
			static_assert(sizeof(PerThreadErrorCounts) == 0xC);

			virtual ~ErrorLogger();	 // 00

			// add
			virtual void PostErrorImpl(const ICachedErrorMessage* a_errMsg, Severity a_severity) = 0;  // 01
			virtual void ResetImpl() { return; }													   // 02

			// members
			const BSFixedString logName;												// 60
			BSSpinLock dataLock;														// 68
			BSTHashMap<std::uint32_t, ErrorLogger::PerThreadErrorCounts> threadErrors;	// 70
		};
		static_assert(sizeof(ErrorLogger) == 0xA0);

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

		class __declspec(novtable) IVirtualMachine :
			public BSIntrusiveRefCounted  // 08
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IVirtualMachine };
			static constexpr auto VTABLE{ VTABLE::BSScript__IVirtualMachine };

			virtual ~IVirtualMachine() = default;  // 00

			// add
			virtual void SetLoader(ILoader* a_newLoader) = 0;																																																															// 01
			virtual void SetLinkedCallback(ITypeLinkedCallback* a_typeLinkedCallback) = 0;																																																								// 02
			virtual void Update(float a_updateBudget) = 0;																																																																// 03
			virtual void UpdateTasklets(float a_updateBudget) = 0;																																																														// 04
			virtual void SetOverstressed(bool a_overstressed) = 0;																																																														// 05
			virtual bool IsCompletelyFrozen() const = 0;																																																																// 06
			virtual bool RegisterObjectType(std::uint32_t a_typeID, const char* a_objectTypeName) = 0;																																																					// 07
			virtual bool GetScriptObjectType(std::uint32_t a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_objType) = 0;																																																	// 09
			virtual bool GetScriptObjectType(const BSFixedString& a_name, BSTSmartPointer<ObjectTypeInfo>& a_objType) = 0;																																																// 08
			virtual bool GetScriptObjectTypeNoLoad(std::uint32_t a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_objType) const = 0;																																														// 0B
			virtual bool GetScriptObjectTypeNoLoad(const BSFixedString& a_objectTypeName, BSTSmartPointer<ObjectTypeInfo>& a_objType) const = 0;																																										// 0A
			virtual bool GetTypeIDForScriptObject(const BSFixedString& a_objectTypeName, std::uint32_t& a_typeID) const = 0;																																															// 0C
			virtual void GetScriptObjectsWithATypeID(BSScrapArray<BSFixedString>& a_objectTypeList) const = 0;																																																			// 0D
			virtual bool GetParentNativeType(const BSFixedString& a_childTypeName, BSTSmartPointer<ObjectTypeInfo>& a_parentType) = 0;																																													// 0E
			virtual bool TypeIsValid(const BSFixedString& a_objectTypeName) = 0;																																																										// 0F
			virtual bool ReloadType(const char* a_objectTypeName) = 0;																																																													// 10
			virtual void TasksToJobs(JobList& a_jobList) = 0;																																																															// 11
			virtual void CalculateFullReloadList(const BSTSet<BSFixedString>& a_scriptSet, BSTObjectArena<BSFixedString>& a_scriptList) const = 0;																																										// 12
			virtual bool GetScriptStructType(const BSFixedString& a_structTypeName, BSTSmartPointer<StructTypeInfo>& a_structType) = 0;																																													// 13
			virtual bool GetScriptStructTypeNoLoad(const BSFixedString& a_structTypeName, BSTSmartPointer<StructTypeInfo>& a_structType) const = 0;																																										// 14
			virtual bool GetChildStructTypes(const BSFixedString& a_parentObjectName, BSTObjectArena<BSFixedString>& a_structTypes) const = 0;																																											// 15
			virtual bool CreateObject(const BSFixedString& a_objectTypeName, BSTSmartPointer<Object>& a_newObj) = 0;																																																	// 17
			virtual bool CreateObject(const BSFixedString& a_objectTypeName, const BSTScrapHashMap<BSFixedString, Variable>& a_properties, BSTSmartPointer<Object>& a_newObj) = 0;																																		// 16
			virtual bool CreateStruct(const BSFixedString& a_structTypeName, BSTSmartPointer<Struct>& a_newStruct) = 0;																																																	// 18
			virtual bool CreateArray(TypeInfo::RawType a_elementType, const BSFixedString& a_elementObjectTypeName, std::uint32_t a_elementCount, BSTSmartPointer<Array>& a_newArray) = 0;																																// 1A
			virtual bool CreateArray(const TypeInfo& a_type, std::uint32_t a_elementCount, BSTSmartPointer<Array>& a_newArray) = 0;																																														// 19
			virtual bool BindNativeMethod(IFunction* a_function) = 0;																																																													// 1B
			virtual void SetCallableFromTasklets(const char* a_objectName, const char* a_functionName, bool a_taskletCallable) = 0;																																														// 1D
			virtual void SetCallableFromTasklets(const char* a_objectName, const char* a_stateName, const char* a_functionName, bool a_taskletCallable) = 0;																																							// 1C
			virtual void ForEachBoundObject(std::uint64_t a_objHandle, const BSTThreadScrapFunction<BSContainer::ForEachResult(Object*)>& a_functor) = 0;																																								// 1E
			virtual bool FindBoundObject(std::uint64_t a_objHandle, const char* a_objectTypeName, bool a_allowConst, BSTSmartPointer<Object>& a_attachedObj, bool a_exactMatch) const = 0;																																// 1F
			virtual void MoveBoundObjects(std::uint64_t a_sourceHandle, std::uint64_t a_destHandle) = 0;																																																				// 20
			virtual void ResetAllBoundObjects(std::uint64_t a_objHandle) = 0;																																																											// 21
			virtual bool CastObject(const BSTSmartPointer<Object>& a_sourceObj, const BSTSmartPointer<ObjectTypeInfo>& a_targetType, BSTSmartPointer<Object>& a_castedObj) = 0;																																			// 22
			virtual bool SetPropertyValue(const BSTSmartPointer<Object>& a_self, const char* a_propName, const Variable& a_newValue, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;																														// 23
			virtual bool GetPropertyValue(const BSTSmartPointer<Object>& a_self, const char* a_propName, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;																																					// 24
			virtual bool GetVariableValue(std::uint64_t a_objHandle, const BSFixedString& a_scriptName, std::uint32_t a_varIndex, Variable& a_var) const = 0;																																							// 26
			virtual bool GetVariableValue(const BSTSmartPointer<Object>& a_obj, std::uint32_t a_varIndex, Variable& a_var) const = 0;																																													// 25
			virtual bool HandleImplementsEvent(std::uint64_t ahObject, const BSFixedString& a_eventName) const = 0;																																																		// 27
			virtual bool AddEventRelay(std::uint64_t a_sourceObject, const BSFixedString& a_eventName, const BSTSmartPointer<Object>& a_destObj) = 0;																																									// 28
			virtual void RemoveEventRelay(std::uint64_t a_sourceObject, const BSFixedString& a_eventName, const BSTSmartPointer<Object>& a_destObj) = 0;																																								// 29
			virtual void RemoveAllEventRelays(const BSTSmartPointer<Object>& a_destObj) = 0;																																																							// 2A
			virtual void SendEvent(std::uint64_t a_objHandle, const BSFixedString& a_eventName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTThreadScrapFunction<bool(const BSTSmartPointer<Object>&)>& a_filter, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;	// 2B
			virtual bool DispatchStaticCall(const BSFixedString& a_objName, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;																	// 2C
			virtual bool DispatchMethodCall(std::uint64_t a_objHandle, const BSFixedString& a_objName, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;										// 2E
			virtual bool DispatchMethodCall(const BSTSmartPointer<Object>& a_self, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;															// 2D
			virtual bool DispatchUnboundMethodCall(std::uint64_t a_objHandle, const BSTSmartPointer<BoundScript>& a_script, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;					// 2F
			virtual bool IsWaitingOnLatent(std::uint32_t a_stackID) const = 0;																																																											// 30
			virtual void ReturnFromLatent(std::uint32_t a_stackID, const Variable& a_retValue) = 0;																																																						// 31
			virtual ErrorLogger& GetErrorLogger() const = 0;																																																															// 32
			virtual const IObjectHandlePolicy& GetObjectHandlePolicy() const = 0;																																																										// 34
			virtual IObjectHandlePolicy& GetObjectHandlePolicy() = 0;																																																													// 33
			virtual const ObjectBindPolicy& GetObjectBindPolicy() const = 0;																																																											// 36
			virtual ObjectBindPolicy& GetObjectBindPolicy() = 0;																																																														// 35
			virtual ISavePatcherInterface& GetSavePatcherInterface() = 0;																																																												// 37
			virtual void RegisterForLogEvent(BSTEventSink<LogEvent>* a_sink) = 0;																																																										// 38
			virtual void UnregisterForLogEvent(BSTEventSink<LogEvent>* a_sink) = 0;																																																										// 39
			virtual void RegisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink) = 0;																																																									// 3A
			virtual void UnregisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink) = 0;																																																									// 3B
			virtual void PostCachedErrorToLogger(const ICachedErrorMessage& a_errorFunctor, ErrorLogger::Severity a_severity) const = 0;																																												// 3D
			virtual void PostCachedErrorToLogger(const ICachedErrorMessage& a_errorFunctor, std::uint32_t aStackID, ErrorLogger::Severity a_severity) const = 0;																																						// 3C
		};
		static_assert(sizeof(IVirtualMachine) == 0x10);

		class __declspec(novtable) IComplexType :
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

		class __declspec(novtable) ObjectTypeInfo :
			public IComplexType	 // 00
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__ObjectTypeInfo };
			static constexpr auto VTABLE{ VTABLE::BSScript__ObjectTypeInfo };

			[[nodiscard]] std::string_view GetName() const { return name; }

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
