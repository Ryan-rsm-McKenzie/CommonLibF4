#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTEvent.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTObjectArena.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/Bethesda/BSTTuple.h"
#include "RE/Bethesda/MemoryManager.h"

namespace RE
{
	template <class F>
	using BSTThreadScrapFunction = msvc::function<F>;

	class BSStorage;

	namespace BSScript
	{
		namespace Internal
		{
			class CodeTasklet;
			class IFuncCallQuery;
			class VirtualMachine;
		}

		namespace UnlinkedTypes
		{
			struct Object;
		}

		class Array;
		class BoundScript;
		class ErrorLogger;
		class ICachedErrorMessage;
		class IComplexType;
		class IFunction;
		class IProfilePolicy;
		class ISavePatcherInterface;
		class IStackCallbackFunctor;
		class IStore;
		class ITypeLinkedCallback;
		class JobList;
		class MemoryPage;
		class Object;
		class ObjectBindPolicy;
		class ObjectTypeInfo;
		class Stack;
		class StackFrame;
		class Struct;
		class StructTypeInfo;
		class Variable;

		struct IHandleReaderWriter;
		struct ILoader;
		struct IMemoryPagePolicy;
		struct IObjectHandlePolicy;
		struct IVMObjectBindInterface;
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
			public BSTEventSource<LogEvent>  // 08
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
				std::uint32_t fatalCount;    // 0
				std::uint32_t errorCount;    // 4
				std::uint32_t warningCount;  // 8
			};
			static_assert(sizeof(PerThreadErrorCounts) == 0xC);

			virtual ~ErrorLogger();  // 00

			// add
			virtual void PostErrorImpl(const ICachedErrorMessage* a_errMsg, Severity a_severity) = 0;  // 01
			virtual void ResetImpl() { return; }                                                       // 02

			// members
			const BSFixedString logName;                                                // 60
			BSSpinLock dataLock;                                                        // 68
			BSTHashMap<std::uint32_t, ErrorLogger::PerThreadErrorCounts> threadErrors;  // 70
		};
		static_assert(sizeof(ErrorLogger) == 0xA0);

		class TypeInfo
		{
		public:
			enum class RawType : std::uint32_t
			{
				kNone,
				kObject,
				kString,
				kInt,
				kFloat,
				kBool,
				kVar,
				kStruct,

				kArrayStart = 10,
				kArrayObject,
				kArrayString,
				kArrayInt,
				kArrayFloat,
				kArrayBool,
				kArrayVar,
				kArrayStruct,
				kArrayEnd
			};

			TypeInfo() noexcept = default;
			TypeInfo(const TypeInfo& a_rhs) noexcept { data.complexTypeInfo = a_rhs.data.complexTypeInfo; }
			TypeInfo(TypeInfo&& a_rhs) noexcept { data.complexTypeInfo = std::exchange(a_rhs.data.complexTypeInfo, nullptr); }
			TypeInfo(RawType a_type) noexcept { data.rawType = a_type; }
			TypeInfo(IComplexType* a_type) noexcept { data.complexTypeInfo = a_type; }

			TypeInfo& operator=(const TypeInfo& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					data.complexTypeInfo = a_rhs.data.complexTypeInfo;
				}
				return *this;
			}

			TypeInfo& operator=(TypeInfo&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					data.complexTypeInfo = std::exchange(a_rhs.data.complexTypeInfo, nullptr);
				}
				return *this;
			}

			TypeInfo& operator=(RawType a_type) noexcept
			{
				data.rawType = a_type;
				return *this;
			}

			TypeInfo& operator=(IComplexType* a_type) noexcept
			{
				data.complexTypeInfo = a_type;
				return *this;
			}

			[[nodiscard]] RawType GetRawType() const;

			[[nodiscard]] bool IsArray() const noexcept
			{
				if (IsComplex()) {
					return data.rawType.all(static_cast<RawType>(1u));
				} else {
					return RawType::kArrayStart < data.rawType && data.rawType < RawType::kArrayEnd;
				}
			}

			[[nodiscard]] bool IsComplex() const noexcept { return data.rawType >= RawType::kArrayEnd; }
			[[nodiscard]] bool IsObject() const { return GetRawType() == RawType::kObject; }

			void SetArray(bool a_set) noexcept
			{
				if (IsComplex()) {
					if (a_set) {
						assert(!IsArray());
						data.rawType.set(static_cast<RawType>(1u));
					} else {
						assert(IsArray());
						data.rawType.reset(static_cast<RawType>(1u));
					}
				} else {
					if (a_set) {
						assert(!IsArray());
						data.rawType += RawType::kArrayStart;
					} else {
						assert(IsArray());
						data.rawType -= RawType::kArrayEnd;
					}
				}
			}

			// members
			union D
			{
				D()
				noexcept :
					complexTypeInfo(nullptr)
				{}

				~D() noexcept { complexTypeInfo = nullptr; }

				stl::enumeration<RawType, std::uintptr_t> rawType;
				IComplexType* complexTypeInfo;
			} data;  // 0
		};
		static_assert(sizeof(TypeInfo) == 0x8);

		class Variable
		{
		public:
			Variable() noexcept = default;
			Variable(const Variable& a_rhs) { copy(a_rhs); }
			Variable(Variable&&) noexcept = default;

			~Variable() { reset(); }

			Variable& operator=(const Variable& a_rhs)
			{
				if (this != std::addressof(a_rhs)) {
					reset();
					copy(a_rhs);
				}
				return *this;
			}

			Variable& operator=(Variable&&) noexcept = default;

			Variable& operator=(std::nullptr_t)
			{
				reset();
				assert(is<std::nullptr_t>());
				return *this;
			}

			Variable& operator=(BSTSmartPointer<Object> a_object);

			Variable& operator=(BSFixedString a_string)
			{
				reset();
				value.s = std::move(a_string);
				varType = RawType::kString;

				assert(is<BSFixedString>());
				return *this;
			}

			Variable& operator=(std::uint32_t a_unsigned)
			{
				reset();
				value.u = a_unsigned;
				varType = RawType::kInt;

				assert(is<std::uint32_t>());
				return *this;
			}

			Variable& operator=(std::int32_t a_signed)
			{
				reset();
				value.i = a_signed;
				varType = RawType::kInt;

				assert(is<std::int32_t>());
				return *this;
			}

			Variable& operator=(float a_float)
			{
				reset();
				value.f = a_float;
				varType = RawType::kFloat;

				assert(is<float>());
				return *this;
			}

			Variable& operator=(bool a_boolean)
			{
				reset();
				value.b = a_boolean;
				varType = RawType::kBool;

				assert(is<bool>());
				return *this;
			}

			Variable& operator=(stl::owner<Variable*> a_variable)
			{
				assert(a_variable != nullptr);
				assert(a_variable->varType.GetRawType() != RawType::kVar);

				reset();
				value.v = a_variable;
				varType = RawType::kVar;
				return *this;
			}

			Variable& operator=(BSTSmartPointer<Struct> a_struct);
			Variable& operator=(BSTSmartPointer<Array> a_array);

			F4_HEAP_REDEFINE_NEW(Variable);

			template <class T>
			[[nodiscard]] friend BSTSmartPointer<Object> get(const Variable& a_var)  //
				requires(std::same_as<T, Object>)
			{
				assert(a_var.is<Object>());
				return a_var.value.o;
			}

			template <class T>
			[[nodiscard]] friend BSFixedString get(const Variable& a_var)  //
				requires(std::same_as<T, BSFixedString>)
			{
				assert(a_var.is<BSFixedString>());
				return a_var.value.s;
			}

			template <class T>
			[[nodiscard]] friend std::uint32_t get(const Variable& a_var)  //
				requires(std::same_as<T, std::uint32_t>)
			{
				assert(a_var.is<std::uint32_t>());
				return a_var.value.u;
			}

			template <class T>
			[[nodiscard]] friend std::int32_t get(const Variable& a_var)  //
				requires(std::same_as<T, std::int32_t>)
			{
				assert(a_var.is<std::int32_t>());
				return a_var.value.i;
			}

			template <class T>
			[[nodiscard]] friend float get(const Variable& a_var)  //
				requires(std::same_as<T, float>)
			{
				assert(a_var.is<float>());
				return a_var.value.f;
			}

			template <class T>
			[[nodiscard]] friend bool get(const Variable& a_var)  //
				requires(std::same_as<T, bool>)
			{
				assert(a_var.is<bool>());
				return a_var.value.b;
			}

			template <class T>
			[[nodiscard]] friend stl::observer<Variable*> get(const Variable& a_var)  //
				requires(std::same_as<T, Variable>)
			{
				assert(a_var.is<Variable>());
				return a_var.value.v;
			}

			template <class T>
			[[nodiscard]] friend BSTSmartPointer<Struct> get(const Variable& a_var)  //
				requires(std::same_as<T, Struct>)
			{
				assert(a_var.is<Struct>());
				return a_var.value.t;
			}

			template <class T>
			[[nodiscard]] friend BSTSmartPointer<Array> get(const Variable& a_var)  //
				requires(std::same_as<T, Array>)
			{
				assert(a_var.is<Array>());
				return a_var.value.a;
			}

			template <class T>
			[[nodiscard]] bool is() const  //
				requires(std::same_as<T, std::nullptr_t>)
			{
				return varType.GetRawType() == RawType::kNone;
			}

			template <class T>
			[[nodiscard]] bool is() const  //
				requires(std::same_as<T, Object>)
			{
				return varType.GetRawType() == RawType::kObject;
			}

			template <class T>
			[[nodiscard]] bool is() const  //
				requires(std::same_as<T, BSFixedString>)
			{
				return varType.GetRawType() == RawType::kString;
			}

			template <class T>
			[[nodiscard]] bool is() const  //
				requires(std::same_as<T, std::uint32_t> ||
						 std::same_as<T, std::int32_t>)
			{
				return varType.GetRawType() == RawType::kInt;
			}

			template <class T>
			[[nodiscard]] bool is() const  //
				requires(std::same_as<T, float>)
			{
				return varType.GetRawType() == RawType::kFloat;
			}

			template <class T>
			[[nodiscard]] bool is() const  //
				requires(std::same_as<T, bool>)
			{
				return varType.GetRawType() == RawType::kBool;
			}

			template <class T>
			[[nodiscard]] bool is() const  //
				requires(std::same_as<T, Variable>)
			{
				return varType.GetRawType() == RawType::kVar;
			}

			template <class T>
			[[nodiscard]] bool is() const  //
				requires(std::same_as<T, Struct>)
			{
				return varType.GetRawType() == RawType::kStruct;
			}

			template <class T>
			[[nodiscard]] bool is() const  //
				requires(std::same_as<T, Array>)
			{
				return varType.IsArray();
			}

			void reset();

		private:
			using RawType = TypeInfo::RawType;

			void copy(const Variable& a_rhs);

			// members
			TypeInfo varType;  // 00
			union V
			{
				// NOLINTNEXTLINE(modernize-use-equals-default)
				V() :
					v(nullptr)
				{}

				V(V&& a_rhs)
				noexcept :
					v(std::exchange(a_rhs.v, nullptr))
				{}

				~V() {}  // NOLINT(modernize-use-equals-default)

				V& operator=(V&& a_rhs) noexcept
				{
					if (this != std::addressof(a_rhs)) {
						v = std::exchange(a_rhs.v, nullptr);
					}
					return *this;
				}

				BSTSmartPointer<Object> o;
				BSFixedString s;
				std::uint32_t u;
				std::int32_t i;
				float f;
				bool b;
				stl::owner<Variable*> v;
				BSTSmartPointer<Struct> t;
				BSTSmartPointer<Array> a;
			} value;  // 08
		};
		static_assert(sizeof(Variable) == 0x10);

		class Object
		{
		public:
			~Object();

			[[nodiscard]] bool Constructed() const noexcept { return constructed; }

			[[nodiscard]] std::uint32_t DecRef() const
			{
				using func_t = decltype(&Object::DecRef);
				REL::Relocation<func_t> func{ REL::ID(541793) };
				return func(this);
			}

			[[nodiscard]] std::size_t GetHandle() const
			{
				using func_t = decltype(&Object::GetHandle);
				REL::Relocation<func_t> func{ REL::ID(1452752) };
				return func(this);
			}

			void IncRef() const
			{
				using func_t = decltype(&Object::IncRef);
				REL::Relocation<func_t> func{ REL::ID(461710) };
				return func(this);
			}

			// members
			std::uint32_t constructed: 1;            // 00:00
			std::uint32_t initialized: 1;            // 00:01
			std::uint32_t valid: 1;                  // 00:02
			std::uint32_t remainingPropsToInit: 29;  // 00:03
			BSTSmartPointer<ObjectTypeInfo> type;    // 08
			BSFixedString currentState;              // 10
			void* lockStructure;                     // 18
			std::size_t handle;                      // 20
			std::uint32_t refCountAndHandleLock;     // 28
			Variable variables[0];                   // 30
		};
		static_assert(sizeof(Object) == 0x30);

		class Struct :
			public BSIntrusiveRefCounted  // 00
		{
		public:
			~Struct();

			// members
			BSSpinLock structLock;                 // 04
			BSTSmartPointer<StructTypeInfo> type;  // 10
			bool constructed{ true };              // 18
			bool valid{ false };                   // 19
			Variable variables[0];                 // 20
		};
		static_assert(sizeof(Struct) == 0x20);

		class Array :
			public BSIntrusiveRefCounted  // 00
		{
		public:
			// members
			TypeInfo elementType;         // 08
			BSSpinLock elementsLock;      // 10
			BSTArray<Variable> elements;  // 18
		};
		static_assert(sizeof(Array) == 0x30);

		class Stack :
			public BSIntrusiveRefCounted  // 00
		{
		public:
			enum class StackType;

			enum class FreezeState
			{
				kUnfrozen,
				kFreezing,
				kFrozen
			};

			enum class State
			{
				kRunning,
				kFinished,
				kWaitingOnMemory,
				kWaitingOnLatentFunction,
				kWaitingInOtherStackForCall,
				kWaitingInOtherStackForReturn,
				kWaitingInOtherStackForReturnNoPop,
				kRetryReturnNoPop,
				kRetryCall
			};

			struct MemoryPageData
			{
			public:
				// members
				BSTAutoPointer<MemoryPage> page;       // 00
				std::uint32_t availableMemoryInBytes;  // 08
			};
			static_assert(sizeof(MemoryPageData) == 0x10);

			[[nodiscard]] std::uint32_t GetPageForFrame(const StackFrame* a_frame) const
			{
				using func_t = decltype(&Stack::GetPageForFrame);
				REL::Relocation<func_t> func{ REL::ID(1429302) };
				return func(this, a_frame);
			}

			[[nodiscard]] Variable& GetStackFrameVariable(const StackFrame* a_frame, std::uint32_t a_index, std::uint32_t a_pageHint)
			{
				using func_t = decltype(&Stack::GetStackFrameVariable);
				REL::Relocation<func_t> func{ REL::ID(897539) };
				return func(this, a_frame, a_index, a_pageHint);
			}

			// members
			IMemoryPagePolicy* policy;                                // 08
			IProfilePolicy* profilePolicy;                            // 10
			BSTSmallArray<MemoryPageData, 3> pages;                   // 18
			std::uint32_t frames;                                     // 58
			StackFrame* top;                                          // 60
			stl::enumeration<State, std::int32_t> state;              // 68
			stl::enumeration<FreezeState, std::int32_t> freezeState;  // 6C
			Variable returnValue;                                     // 70
			std::uint32_t stackID;                                    // 80
			stl::enumeration<StackType, std::int32_t> stackType;      // 84
			BSTSmartPointer<Internal::CodeTasklet> owningTasklet;     // 88
			BSTSmartPointer<IStackCallbackFunctor> callback;          // 90
			BSTSmartPointer<Object> objToUnbind;                      // 98
			BSTSmartPointer<Stack> nextStack;                         // A0
		};
		static_assert(sizeof(Stack) == 0xA8);

		class StackFrame
		{
		public:
			// members
			Stack* parent;                                     // 00
			StackFrame* previousFrame;                         // 08
			BSTSmartPointer<IFunction> owningFunction;         // 10
			BSTSmartPointer<ObjectTypeInfo> owningObjectType;  // 18
			std::uint32_t ip;                                  // 20
			Variable self;                                     // 28
			std::uint32_t size;                                // 38
			bool instructionsValid;                            // 3C
		};
		static_assert(sizeof(StackFrame) == 0x40);

		class __declspec(novtable) IVirtualMachine :
			public BSIntrusiveRefCounted  // 08
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IVirtualMachine };
			static constexpr auto VTABLE{ VTABLE::BSScript__IVirtualMachine };

			virtual ~IVirtualMachine() = default;  // 00

			// add
			virtual void SetLoader(ILoader* a_newLoader) = 0;                                                                                                                                                                                                                                                           // 01
			virtual void SetLinkedCallback(ITypeLinkedCallback* a_typeLinkedCallback) = 0;                                                                                                                                                                                                                              // 02
			virtual void Update(float a_updateBudget) = 0;                                                                                                                                                                                                                                                              // 03
			virtual void UpdateTasklets(float a_updateBudget) = 0;                                                                                                                                                                                                                                                      // 04
			virtual void SetOverstressed(bool a_overstressed) = 0;                                                                                                                                                                                                                                                      // 05
			virtual bool IsCompletelyFrozen() const = 0;                                                                                                                                                                                                                                                                // 06
			virtual bool RegisterObjectType(std::uint32_t a_typeID, const char* a_objectTypeName) = 0;                                                                                                                                                                                                                  // 07
			virtual bool GetScriptObjectType(std::uint32_t a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_objType) = 0;                                                                                                                                                                                                   // 09
			virtual bool GetScriptObjectType(const BSFixedString& a_name, BSTSmartPointer<ObjectTypeInfo>& a_objType) = 0;                                                                                                                                                                                              // 08
			virtual bool GetScriptObjectTypeNoLoad(std::uint32_t a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_objType) const = 0;                                                                                                                                                                                       // 0B
			virtual bool GetScriptObjectTypeNoLoad(const BSFixedString& a_objectTypeName, BSTSmartPointer<ObjectTypeInfo>& a_objType) const = 0;                                                                                                                                                                        // 0A
			virtual bool GetTypeIDForScriptObject(const BSFixedString& a_objectTypeName, std::uint32_t& a_typeID) const = 0;                                                                                                                                                                                            // 0C
			virtual void GetScriptObjectsWithATypeID(BSScrapArray<BSFixedString>& a_objectTypeList) const = 0;                                                                                                                                                                                                          // 0D
			virtual bool GetParentNativeType(const BSFixedString& a_childTypeName, BSTSmartPointer<ObjectTypeInfo>& a_parentType) = 0;                                                                                                                                                                                  // 0E
			virtual bool TypeIsValid(const BSFixedString& a_objectTypeName) = 0;                                                                                                                                                                                                                                        // 0F
			virtual bool ReloadType(const char* a_objectTypeName) = 0;                                                                                                                                                                                                                                                  // 10
			virtual void TasksToJobs(JobList& a_jobList) = 0;                                                                                                                                                                                                                                                           // 11
			virtual void CalculateFullReloadList(const BSTSet<BSFixedString>& a_scriptSet, BSTObjectArena<BSFixedString>& a_scriptList) const = 0;                                                                                                                                                                      // 12
			virtual bool GetScriptStructType(const BSFixedString& a_structTypeName, BSTSmartPointer<StructTypeInfo>& a_structType) = 0;                                                                                                                                                                                 // 13
			virtual bool GetScriptStructTypeNoLoad(const BSFixedString& a_structTypeName, BSTSmartPointer<StructTypeInfo>& a_structType) const = 0;                                                                                                                                                                     // 14
			virtual bool GetChildStructTypes(const BSFixedString& a_parentObjectName, BSTObjectArena<BSFixedString>& a_structTypes) const = 0;                                                                                                                                                                          // 15
			virtual bool CreateObject(const BSFixedString& a_objectTypeName, BSTSmartPointer<Object>& a_newObj) = 0;                                                                                                                                                                                                    // 17
			virtual bool CreateObject(const BSFixedString& a_objectTypeName, const BSTScrapHashMap<BSFixedString, Variable>& a_properties, BSTSmartPointer<Object>& a_newObj) = 0;                                                                                                                                      // 16
			virtual bool CreateStruct(const BSFixedString& a_structTypeName, BSTSmartPointer<Struct>& a_newStruct) = 0;                                                                                                                                                                                                 // 18
			virtual bool CreateArray(TypeInfo::RawType a_elementType, const BSFixedString& a_elementObjectTypeName, std::uint32_t a_elementCount, BSTSmartPointer<Array>& a_newArray) = 0;                                                                                                                              // 1A
			virtual bool CreateArray(const TypeInfo& a_type, std::uint32_t a_elementCount, BSTSmartPointer<Array>& a_newArray) = 0;                                                                                                                                                                                     // 19
			virtual bool BindNativeMethod(IFunction* a_function) = 0;                                                                                                                                                                                                                                                   // 1B
			virtual void SetCallableFromTasklets(const char* a_objectName, const char* a_functionName, bool a_taskletCallable) = 0;                                                                                                                                                                                     // 1D
			virtual void SetCallableFromTasklets(const char* a_objectName, const char* a_stateName, const char* a_functionName, bool a_taskletCallable) = 0;                                                                                                                                                            // 1C
			virtual void ForEachBoundObject(std::uint64_t a_objHandle, const BSTThreadScrapFunction<BSContainer::ForEachResult(Object*)>& a_functor) = 0;                                                                                                                                                               // 1E
			virtual bool FindBoundObject(std::uint64_t a_objHandle, const char* a_objectTypeName, bool a_allowConst, BSTSmartPointer<Object>& a_attachedObj, bool a_exactMatch) const = 0;                                                                                                                              // 1F
			virtual void MoveBoundObjects(std::uint64_t a_sourceHandle, std::uint64_t a_destHandle) = 0;                                                                                                                                                                                                                // 20
			virtual void ResetAllBoundObjects(std::uint64_t a_objHandle) = 0;                                                                                                                                                                                                                                           // 21
			virtual bool CastObject(const BSTSmartPointer<Object>& a_sourceObj, const BSTSmartPointer<ObjectTypeInfo>& a_targetType, BSTSmartPointer<Object>& a_castedObj) = 0;                                                                                                                                         // 22
			virtual bool SetPropertyValue(const BSTSmartPointer<Object>& a_self, const char* a_propName, const Variable& a_newValue, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;                                                                                                                     // 23
			virtual bool GetPropertyValue(const BSTSmartPointer<Object>& a_self, const char* a_propName, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;                                                                                                                                                 // 24
			virtual bool GetVariableValue(std::uint64_t a_objHandle, const BSFixedString& a_scriptName, std::uint32_t a_varIndex, Variable& a_var) const = 0;                                                                                                                                                           // 26
			virtual bool GetVariableValue(const BSTSmartPointer<Object>& a_obj, std::uint32_t a_varIndex, Variable& a_var) const = 0;                                                                                                                                                                                   // 25
			virtual bool HandleImplementsEvent(std::uint64_t a_object, const BSFixedString& a_eventName) const = 0;                                                                                                                                                                                                     // 27
			virtual bool AddEventRelay(std::uint64_t a_sourceObject, const BSFixedString& a_eventName, const BSTSmartPointer<Object>& a_destObj) = 0;                                                                                                                                                                   // 28
			virtual void RemoveEventRelay(std::uint64_t a_sourceObject, const BSFixedString& a_eventName, const BSTSmartPointer<Object>& a_destObj) = 0;                                                                                                                                                                // 29
			virtual void RemoveAllEventRelays(const BSTSmartPointer<Object>& a_destObj) = 0;                                                                                                                                                                                                                            // 2A
			virtual void SendEvent(std::uint64_t a_objHandle, const BSFixedString& a_eventName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTThreadScrapFunction<bool(const BSTSmartPointer<Object>&)>& a_filter, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;  // 2B
			virtual bool DispatchStaticCall(const BSFixedString& a_objName, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;                                                                   // 2C
			virtual bool DispatchMethodCall(std::uint64_t a_objHandle, const BSFixedString& a_objName, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;                                        // 2E
			virtual bool DispatchMethodCall(const BSTSmartPointer<Object>& a_self, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;                                                            // 2D
			virtual bool DispatchUnboundMethodCall(std::uint64_t a_objHandle, const BSTSmartPointer<BoundScript>& a_script, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;                   // 2F
			virtual bool IsWaitingOnLatent(std::uint32_t a_stackID) const = 0;                                                                                                                                                                                                                                          // 30
			virtual void ReturnFromLatent(std::uint32_t a_stackID, const Variable& a_retValue) = 0;                                                                                                                                                                                                                     // 31
			[[nodiscard]] virtual ErrorLogger& GetErrorLogger() const = 0;                                                                                                                                                                                                                                              // 32
			[[nodiscard]] virtual const IObjectHandlePolicy& GetObjectHandlePolicy() const = 0;                                                                                                                                                                                                                         // 34
			[[nodiscard]] virtual IObjectHandlePolicy& GetObjectHandlePolicy() = 0;                                                                                                                                                                                                                                     // 33
			[[nodiscard]] virtual const ObjectBindPolicy& GetObjectBindPolicy() const = 0;                                                                                                                                                                                                                              // 36
			[[nodiscard]] virtual ObjectBindPolicy& GetObjectBindPolicy() = 0;                                                                                                                                                                                                                                          // 35
			[[nodiscard]] virtual ISavePatcherInterface& GetSavePatcherInterface() = 0;                                                                                                                                                                                                                                 // 37
			virtual void RegisterForLogEvent(BSTEventSink<LogEvent>* a_sink) = 0;                                                                                                                                                                                                                                       // 38
			virtual void UnregisterForLogEvent(BSTEventSink<LogEvent>* a_sink) = 0;                                                                                                                                                                                                                                     // 39
			virtual void RegisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink) = 0;                                                                                                                                                                                                                                   // 3A
			virtual void UnregisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink) = 0;                                                                                                                                                                                                                                 // 3B
			virtual void PostCachedErrorToLogger(const ICachedErrorMessage& a_errorFunctor, ErrorLogger::Severity a_severity) const = 0;                                                                                                                                                                                // 3D
			virtual void PostCachedErrorToLogger(const ICachedErrorMessage& a_errorFunctor, std::uint32_t a_stackID, ErrorLogger::Severity a_severity) const = 0;                                                                                                                                                       // 3C

			template <class F>
			void BindNativeMethod(
				stl::zstring a_object,
				stl::zstring a_function,
				F a_func,
				std::optional<bool> a_taskletCallable = std::nullopt,
				bool a_isLatent = false);

			void PostError(std::string_view a_msg, std::uint32_t a_stackID, ErrorLogger::Severity a_severity)
			{
				class ErrorImpl :
					public ICachedErrorMessage
				{
				public:
					ErrorImpl(std::string_view a_message) noexcept :
						_message(a_message)
					{}

					void GetErrorMsg(BSFixedString& a_message) const override { a_message = _message; }

				private:
					std::string_view _message;
				};

				const ErrorImpl e{ a_msg };
				PostCachedErrorToLogger(e, a_stackID, a_severity);
			}
		};
		static_assert(sizeof(IVirtualMachine) == 0x10);

		class __declspec(novtable) IClientVM
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IClientVM };
			static constexpr auto VTABLE{ VTABLE::BSScript__IClientVM };

			virtual ~IClientVM();  // 00

			// add
			virtual bool IsVMFrozen() const;  // 01
			virtual void PreSave();           // 02
		};
		static_assert(sizeof(IClientVM) == 0x8);

		class __declspec(novtable) IStackCallbackSaveInterface
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IStackCallbackSaveInterface };
			static constexpr auto VTABLE{ VTABLE::BSScript__IStackCallbackSaveInterface };

			virtual ~IStackCallbackSaveInterface();  // 00

			// add
			virtual bool SaveStackCallback(BSStorage& a_buffer, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) const;         // 01
			virtual bool LoadStackCallback(const BSStorage& a_buffer, bool&, BSTSmartPointer<IStackCallbackFunctor>& a_callback) const;  // 02
		};
		static_assert(sizeof(IStackCallbackSaveInterface) == 0x8);

		class __declspec(novtable) IComplexType :
			public BSIntrusiveRefCounted  // 08
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IComplexType };
			static constexpr auto VTABLE{ VTABLE::BSScript__IComplexType };

			virtual ~IComplexType() = 0;  // 00

			// add
			virtual TypeInfo::RawType GetRawType() const = 0;  // 01

			[[nodiscard]] bool IsObject() const { return GetRawType() == TypeInfo::RawType::kObject; }
		};
		static_assert(sizeof(IComplexType) == 0x10);

		class PropertyGroupInfo :
			public BSIntrusiveRefCounted  // 00
		{
		public:
			// members
			BSFixedString groupName;                // 08
			BSFixedString docString;                // 10
			std::uint32_t userFlags;                // 18
			BSTArray<BSFixedString> propertyNames;  // 20
		};
		static_assert(sizeof(PropertyGroupInfo) == 0x38);

		class __declspec(novtable) ObjectTypeInfo :
			public IComplexType  // 00
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__ObjectTypeInfo };
			static constexpr auto VTABLE{ VTABLE::BSScript__ObjectTypeInfo };

			enum class LinkValidState : std::uint32_t
			{
				kNotLinked,
				kCurrentlyLinking,
				kLinkedInvalid,
				kLinkedValid
			};

			[[nodiscard]] std::uint32_t GetVariableCount() const noexcept
			{
				std::uint32_t count = 0;
				for (BSTSmartPointer iter{ this }; iter && iter->Valid(); iter = iter->parentTypeInfo) {
					count += iter->variableCount;
				}
				return count;
			}

			[[nodiscard]] bool Valid() const noexcept { return linkedValid == LinkValidState::kLinkedValid; }

			// members
			BSFixedString name;                                           // 10
			BSTSmartPointer<ObjectTypeInfo> parentTypeInfo;               // 18
			BSFixedString docString;                                      // 20
			BSTArray<BSTSmartPointer<PropertyGroupInfo>> propertyGroups;  // 28
			LinkValidState linkedValid: 2;                                // 40:00
			std::uint32_t isConst: 1;                                     // 40:02
			std::uint32_t userFlagCount: 5;                               // 40:03
			std::uint32_t variableCount: 10;                              // 40:08
			std::uint32_t variableUserFlagCount: 6;                       // 40:18
			std::uint32_t initialValueCount: 10;                          // 44:00
			std::uint32_t propertyCount: 10;                              // 44:10
			std::uint32_t staticFunctionCount: 9;                         // 44:20
			std::uint32_t emptyStateMemberFunctionCount: 11;              // 48:00
			std::uint32_t namedStateCount: 7;                             // 48:11
			std::uint32_t initialState: 7;                                // 48:18
			void* data;                                                   // 50
		};
		static_assert(sizeof(ObjectTypeInfo) == 0x58);

		class __declspec(novtable) StructTypeInfo :
			public IComplexType  // 00
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__StructTypeInfo };
			static constexpr auto VTABLE{ VTABLE::BSScript__StructTypeInfo };

			enum class LinkValidState
			{
				kNotLinked,
				kCurrentlyLinking,
				kLinkedInvalid,
				kLinkedValid
			};

			struct StructVar
			{
			public:
				// members
				Variable initialValue;    // 00
				TypeInfo varType;         // 10
				BSFixedString docString;  // 18
				std::uint32_t userFlags;  // 20
				bool isConst;             // 24
			};
			static_assert(sizeof(StructVar) == 0x28);

			// members
			BSFixedString name;                                          // 10
			BSTSmartPointer<ObjectTypeInfo> containingObjTypeInfo;       // 18
			BSTArray<StructVar> variables;                               // 20
			BSTHashMap<BSFixedString, std::uint32_t> varNameIndexMap;    // 38
			stl::enumeration<LinkValidState, std::int32_t> linkedValid;  // 68
		};
		static_assert(sizeof(StructTypeInfo) == 0x70);

		struct __declspec(novtable) IMemoryPagePolicy
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IMemoryPagePolicy };
			static constexpr auto VTABLE{ VTABLE::BSScript__IMemoryPagePolicy };

			enum class AllocationStatus;
			enum class NewPageStrategy;

			virtual ~IMemoryPagePolicy() = default;  // 00

			// add
			virtual std::uint32_t MaximumPageSize() const = 0;                                                                                          // 01
			virtual std::uint32_t MaximumStackDepth() const = 0;                                                                                        // 02
			virtual AllocationStatus AllocatePage(std::uint32_t a_sizeInBytes, NewPageStrategy a_strategy, BSTAutoPointer<MemoryPage>& a_newPage) = 0;  // 03
			virtual AllocationStatus GetLargestAvailablePage(BSTAutoPointer<MemoryPage>& a_newPage) = 0;                                                // 04
			virtual void DisposePage(BSTAutoPointer<MemoryPage>& a_oldPage) = 0;                                                                        // 05
		};
		static_assert(sizeof(IMemoryPagePolicy) == 0x8);

		class __declspec(novtable) SimpleAllocMemoryPagePolicy :
			public IMemoryPagePolicy
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__SimpleAllocMemoryPagePolicy };
			static constexpr auto VTABLE{ VTABLE::BSScript__SimpleAllocMemoryPagePolicy };

			// override (IMemoryPagePolicy)
			std::uint32_t MaximumPageSize() const override { return maxPageSize; }                                                                   // 01
			std::uint32_t MaximumStackDepth() const override { return maxStackDepth; }                                                               // 02
			AllocationStatus AllocatePage(std::uint32_t a_sizeInBytes, NewPageStrategy a_strategy, BSTAutoPointer<MemoryPage>& a_newPage) override;  // 03
			AllocationStatus GetLargestAvailablePage(BSTAutoPointer<MemoryPage>& a_newPage) override;                                                // 04
			void DisposePage(BSTAutoPointer<MemoryPage>& a_oldPage) override;                                                                        // 05

			// members
			const std::uint32_t minPageSize{ 0x80 };            // 08
			const std::uint32_t maxPageSize{ 0x200 };           // 0C
			const std::uint32_t maxAllocatedMemory{ 0x25800 };  // 10
			const std::uint32_t maxStackDepth{ 0x64 };          // 14
			bool ignoreMemoryLimit;                             // 18
			bool outOfMemory;                                   // 19
			BSSpinLock dataLock;                                // 1C
			std::uint32_t currentMemorySize;                    // 24
			std::uint32_t maxAdditionalAllocations;             // 28
		};
		static_assert(sizeof(SimpleAllocMemoryPagePolicy) == 0x30);

		struct __declspec(novtable) ILoader
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__ILoader };
			static constexpr auto VTABLE{ VTABLE::BSScript__ILoader };

			virtual ~ILoader() = default;  // 00

			// add
			virtual ILoader* Clone() const = 0;                                                     // 01
			virtual void SetScriptStore(const BSTSmartPointer<IStore>& a_newStore) = 0;             // 02
			virtual bool GetClass(const char* a_name, UnlinkedTypes::Object& a_unlinkedClass) = 0;  // 03
		};
		static_assert(sizeof(ILoader) == 0x8);

		namespace Internal
		{
			enum class StringIndexSize
			{
				kSmall,
				kLarge
			};

			class ReadableStringTable
			{
			public:
				class StringEntry
				{
				public:
					// members
					const char* originalData;       // 00
					BSFixedString convertedString;  // 08
				};
				static_assert(sizeof(StringEntry) == 0x10);

				class StringTableScrapPage
				{
				public:
					// members
					char buffer[0x1000];    // 0000
					char* curr;             // 1000
					const char* const end;  // 1008
				};
				static_assert(sizeof(StringTableScrapPage) == 0x1010);

				// members
				msvc::unique_ptr<BSTObjectArena<StringTableScrapPage, BSTObjectArenaScrapAlloc, 1>> scrapPages;  // 00
				msvc::unique_ptr<BSScrapArray<StringEntry>> entries;                                             // 08
				stl::enumeration<StringIndexSize, std::int32_t> indexSize;                                       // 10
			};
			static_assert(sizeof(ReadableStringTable) == 0x18);
		}

		class __declspec(novtable) CompiledScriptLoader :
			public ILoader  // 00
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__CompiledScriptLoader };
			static constexpr auto VTABLE{ VTABLE::BSScript__CompiledScriptLoader };

			// override (ILoader)
			ILoader* Clone() const override;                                                     // 01
			void SetScriptStore(const BSTSmartPointer<IStore>& a_newStore) override;             // 02
			bool GetClass(const char* a_name, UnlinkedTypes::Object& a_unlinkedClass) override;  // 03

			// members
			ErrorLogger* errorHandler;                  // 08
			BSTSmartPointer<IStore> scriptStore;        // 10
			Internal::ReadableStringTable stringTable;  // 18
			std::int8_t fileMajorVersion;               // 30
			std::int8_t fileMinorVersion;               // 31
			std::int8_t loadFlags;                      // 32
		};
		static_assert(sizeof(CompiledScriptLoader) == 0x38);

		struct __declspec(novtable) IObjectHandlePolicy
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IObjectHandlePolicy };
			static constexpr auto VTABLE{ VTABLE::BSScript__IObjectHandlePolicy };

			virtual ~IObjectHandlePolicy() = default;  // 00

			// add
			virtual bool HandleIsType(std::uint32_t a_type, std::size_t a_handle) const = 0;               // 01
			virtual bool GetHandleType(std::size_t a_handle, std::uint32_t& a_type) const = 0;             // 02
			virtual bool IsHandleLoaded(std::size_t a_handle) const = 0;                                   // 03
			virtual bool IsHandleObjectAvailable(std::size_t a_handle) const = 0;                          // 04
			virtual bool ShouldAttemptToCleanHandle(std::size_t a_handle) const = 0;                       // 05
			virtual std::size_t EmptyHandle() const = 0;                                                   // 06
			virtual std::size_t GetHandleForObject(std::uint32_t a_type, const void* a_object) const = 0;  // 07
			virtual bool HasParent(std::size_t a_childHandle) const = 0;                                   // 08
			virtual std::size_t GetParentHandle(std::size_t a_childHandle) const = 0;                      // 09
			virtual std::size_t GetHandleScriptsMovedFrom(std::size_t a_newHandle) const = 0;              // 0A
			virtual std::size_t GetSaveRemappedHandle(std::size_t a_saveHandle) const = 0;                 // 0B
			virtual void* GetObjectForHandle(std::uint32_t a_type, std::size_t a_handle) const = 0;        // 0C
			virtual void PersistHandle(std::size_t a_handle) = 0;                                          // 0D
			virtual void ReleaseHandle(std::size_t a_handle) = 0;                                          // 0E
			virtual void ConvertHandleToString(std::size_t a_handle, BSFixedString& a_string) const = 0;   // 0F
		};
		static_assert(sizeof(IObjectHandlePolicy) == 0x8);

		class MergedBoundScript
		{
		public:
			// members
			BSTSmartPointer<BoundScript> childScript;   // 00
			BSTSmartPointer<BoundScript> parentScript;  // 08
		};
		static_assert(sizeof(MergedBoundScript) == 0x10);

		class __declspec(novtable) ObjectBindPolicy
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__ObjectBindPolicy };
			static constexpr auto VTABLE{ VTABLE::BSScript__ObjectBindPolicy };

			virtual ~ObjectBindPolicy();  // 00

			// add
			virtual void EnsureBaseDataLoaded(std::size_t a_objHandle) = 0;                                                                                                                                                                           // 01
			virtual void ObjectNoLongerNeeded(std::size_t a_objHandle) = 0;                                                                                                                                                                           // 02
			virtual void AddBoundInfoImpl(std::size_t a_objHandle) = 0;                                                                                                                                                                               // 03
			virtual void ClearBoundInfoImpl(std::size_t a_objHandle) = 0;                                                                                                                                                                             // 04
			virtual void ClearDiskLoadedBoundInfoImpl(std::size_t a_objHandle) = 0;                                                                                                                                                                   // 05
			virtual void ClearAllBoundInfoImpl() = 0;                                                                                                                                                                                                 // 06
			virtual void PostBindObject(std::size_t a_objHandle) = 0;                                                                                                                                                                                 // 07
			virtual std::uint32_t GetExtraInfoSize(std::size_t) const = 0;                                                                                                                                                                            // 08
			virtual void WriteExtraInfo(std::size_t, const IHandleReaderWriter&, BSStorage&) const = 0;                                                                                                                                               // 09
			virtual void ReadExtraInfo(std::size_t a_objHandle, std::uint16_t a_handleVersion, const IHandleReaderWriter& a_handleReaderWriter, const BSStorage& a_storage) = 0;                                                                      // 0A
			virtual bool IsIgnoringClear() const = 0;                                                                                                                                                                                                 // 0B
			virtual void ResolveProperties(std::size_t a_objTarget, const BSTSmartPointer<Object>& a_object, const BSTSmartPointer<BoundScript>& a_boundScript, bool a_postSaveConstOnly) = 0;                                                        // 0D
			virtual void ResolveProperties(std::size_t a_objTarget, const BSTSmartPointer<Object>& a_object, const MergedBoundScript& a_boundScript, bool a_postSaveConstOnly) = 0;                                                                   // 0C
			virtual void ConvertProperties(std::size_t a_objTarget, const BSTSmartPointer<BoundScript>& a_boundScript, bool a_constOnly, BSTScrapHashMap<BSFixedString, Variable>& a_properties, std::uint32_t& a_nonConvertedProperties) const = 0;  // 0F
			virtual void ConvertProperties(std::size_t a_objTarget, const MergedBoundScript& a_mergedScript, bool a_constOnly, BSTScrapHashMap<BSFixedString, Variable>& a_properties, std::uint32_t& a_nonConvertedProperties) const = 0;            // 0E

			void BindObject(const BSTSmartPointer<Object>& a_obj, std::size_t a_objHandle)
			{
				using func_t = decltype(&ObjectBindPolicy::BindObject);
				REL::Relocation<func_t> func{ REL::ID(709728) };
				return func(this, a_obj, a_objHandle);
			}

			// members
			IVirtualMachine* vm;                                                                         // 10
			IVMObjectBindInterface* bindInterface;                                                       // 18
			BSSpinLock attachedScriptsLock;                                                              // 20
			BSTHashMap<std::size_t, BSTSmallSharedArray<BSTSmartPointer<BoundScript>>> attachedScripts;  // 50
		};
		static_assert(sizeof(ObjectBindPolicy) == 0x50);

		class __declspec(novtable) IProfilePolicy
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__IProfilePolicy };
			static constexpr auto VTABLE{ VTABLE::BSScript__IProfilePolicy };

			virtual ~IProfilePolicy() = default;  // 00

			// add
			virtual void StackFramePushQueued(std::uint32_t a_stackID, std::uint32_t a_frameNumber, const BSTSmartPointer<Internal::IFuncCallQuery>& a_funcCallQuery) = 0;                                                                 // 01
			virtual void StackFramePushed(std::uint32_t a_stackID, std::uint32_t a_frameNumber, const Variable& a_self, const BSFixedString& a_scriptName, const BSFixedString& a_stateName, const BSFixedString& a_functionName) = 0;     // 02
			virtual void StackFramePopQueued(std::uint32_t a_stackID, std::uint32_t a_frameNumber, const Variable& a_self, const BSFixedString& a_scriptName, const BSFixedString& a_stateName, const BSFixedString& a_functionName) = 0;  // 03
			virtual void StackFramePopped(std::uint32_t a_stackID, std::uint32_t a_frameNumber, const Variable& a_self, const BSFixedString& a_scriptName, const BSFixedString& a_stateName, const BSFixedString& a_functionName) = 0;     // 04
		};
		static_assert(sizeof(IProfilePolicy) == 0x8);

		class ISavePatcherInterface
		{
		public:
			static constexpr auto RTTI{ RTTI::BSScript__ISavePatcherInterface };
			static constexpr auto VTABLE{ VTABLE::BSScript__ISavePatcherInterface };

			virtual ~ISavePatcherInterface() = default;  // 00

			// add
			virtual void PatchStackFrame(StackFrame&, IVirtualMachine&) = 0;  // 01
		};
		static_assert(sizeof(ISavePatcherInterface) == 0x8);

		namespace Internal
		{
			class VDescTable
			{
			public:
				using value_type = BSTTuple<BSFixedString, TypeInfo>;
				using size_type = std::uint16_t;

				VDescTable(size_type a_params, size_type a_locals) :
					paramCount(a_params),
					totalEntries(a_params + a_locals)
				{
					const auto total = paramCount + totalEntries;
					if (total > 0) {
						entries = new value_type[total];
					}
				}

				~VDescTable() { delete[] entries; }

				// members
				value_type* entries{ nullptr };  // 00
				size_type paramCount{ 0 };       // 08
				size_type totalEntries{ 0 };     // 0A
			};
			static_assert(sizeof(VDescTable) == 0x10);
		}

		class __declspec(novtable) IFunction :
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

			virtual ~IFunction() = default;  // 00

			// add
			virtual const BSFixedString& GetName() const = 0;                                                                                                              // 01
			virtual const BSFixedString& GetObjectTypeName() const = 0;                                                                                                    // 02
			virtual const BSFixedString& GetStateName() const = 0;                                                                                                         // 03
			virtual TypeInfo GetReturnType() const = 0;                                                                                                                    // 04
			virtual std::uint32_t GetParamCount() const = 0;                                                                                                               // 05
			virtual void GetParam(std::uint32_t a_param, BSFixedString& a_paramName, TypeInfo& a_paramType) const = 0;                                                     // 06
			virtual std::uint32_t GetStackFrameSize() const = 0;                                                                                                           // 07
			virtual bool GetIsNative() const = 0;                                                                                                                          // 08
			virtual bool GetIsStatic() const = 0;                                                                                                                          // 09
			virtual bool GetIsEmpty() const = 0;                                                                                                                           // 0A
			virtual FunctionType GetFunctionType() const = 0;                                                                                                              // 0B
			virtual std::uint32_t GetUserFlags() const = 0;                                                                                                                // 0C
			virtual const BSFixedString& GetDocString() const = 0;                                                                                                         // 0D
			virtual void InsertLocals(StackFrame& a_frame) const = 0;                                                                                                      // 0E
			virtual CallResult Call(const BSTSmartPointer<Stack>& a_stack, ErrorLogger& a_errorLogger, Internal::VirtualMachine& a_vm, bool a_inScriptTasklet) const = 0;  // 0F
			virtual const BSFixedString& GetSourceFilename() const = 0;                                                                                                    // 10
			virtual bool TranslateIPToLineNumber(std::uint32_t a_ip, std::uint32_t& a_lineNumber) const = 0;                                                               // 11
			virtual bool GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_variableName) const = 0;                                                          // 12
			virtual bool CanBeCalledFromTasklets() const = 0;                                                                                                              // 13
			virtual void SetCallableFromTasklets(bool a_taskletCallable) = 0;                                                                                              // 14

			F4_HEAP_REDEFINE_NEW(IFunction);
		};
		static_assert(sizeof(IFunction) == 0x10);

		namespace NF_util
		{
			class __declspec(novtable) NativeFunctionBase :
				public IFunction  // 00
			{
			public:
				static constexpr auto RTTI{ RTTI::BSScript__NF_util__NativeFunctionBase };
				static constexpr auto VTABLE{ VTABLE::BSScript__NF_util__NativeFunctionBase };

				NativeFunctionBase(
					std::string_view a_object,
					std::string_view a_function,
					std::uint16_t a_paramCount,
					bool a_isStatic,
					bool a_isLatent) :
					name(a_function),
					objName(a_object),
					descTable(a_paramCount, 0),
					isStatic(a_isStatic),
					isLatent(a_isLatent)
				{
					for (std::size_t i = 0; i < descTable.paramCount; ++i) {
						descTable.entries[i].first = fmt::format(FMT_STRING("param{}"), i + 1);
					}
				}

				// override (IFunction)
				const BSFixedString& GetName() const override { return name; }                   // 01
				const BSFixedString& GetObjectTypeName() const override { return objName; }      // 02
				const BSFixedString& GetStateName() const override { return stateName; }         // 03
				TypeInfo GetReturnType() const override { return retType; }                      // 04
				std::uint32_t GetParamCount() const override { return descTable.totalEntries; }  // 05

				void GetParam(std::uint32_t a_param, BSFixedString& a_paramName, TypeInfo& a_paramType) const override  // 06
				{
					if (a_param < descTable.paramCount) {
						assert(descTable.entries != nullptr);
						const auto& entry = descTable.entries[a_param];
						a_paramName = entry.first;
						a_paramType = entry.second;
					} else {
						a_paramName = ""sv;
						a_paramType = nullptr;
					}
				}

				std::uint32_t GetStackFrameSize() const override { return descTable.totalEntries; }  // 07
				bool GetIsNative() const override { return true; }                                   // 08
				bool GetIsStatic() const override { return isStatic; }                               // 09
				bool GetIsEmpty() const override { return false; }                                   // 0A
				FunctionType GetFunctionType() const override { return FunctionType::kNormal; }      // 0B
				std::uint32_t GetUserFlags() const override { return userFlags; }                    // 0C
				const BSFixedString& GetDocString() const override { return docString; }             // 0D
				void InsertLocals(StackFrame&) const override { return; }                            // 0E

				CallResult Call(const BSTSmartPointer<Stack>& a_stack, ErrorLogger& a_errorLogger, Internal::VirtualMachine& a_vm, bool a_inScriptTasklet) const override  // 0F
				{
					using func_t = decltype(&NativeFunctionBase::Call);
					REL::Relocation<func_t> func{ REL::ID(571037) };
					return func(this, a_stack, a_errorLogger, a_vm, a_inScriptTasklet);
				}

				const BSFixedString& GetSourceFilename() const override  // 10
				{
					static BSFixedString native{ "<native>"sv };
					return native;
				}

				bool TranslateIPToLineNumber(std::uint32_t, std::uint32_t& a_lineNumber) const override  // 11
				{
					a_lineNumber = 0;
					return false;
				}

				bool GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_variableName) const override  // 12
				{
					if (a_index < descTable.totalEntries) {
						assert(descTable.entries != nullptr);
						a_variableName = descTable.entries[a_index].first;
						return true;
					} else {
						a_variableName = "";
						return false;
					}
				}

				bool CanBeCalledFromTasklets() const override { return isCallableFromTasklet; }                               // 13
				void SetCallableFromTasklets(bool a_taskletCallable) override { isCallableFromTasklet = a_taskletCallable; }  // 14

				// add
				virtual bool HasStub() const = 0;                                                                                                                                           // 15
				virtual bool MarshallAndDispatch(Variable& a_self, Internal::VirtualMachine& a_vm, std::uint32_t a_stackID, Variable& a_retVal, const StackFrame& a_stackFrame) const = 0;  // 16

				// members
				BSFixedString name;                   // 10
				BSFixedString objName;                // 18
				BSFixedString stateName{ "" };        // 20
				TypeInfo retType;                     // 28
				Internal::VDescTable descTable;       // 30
				bool isStatic;                        // 40
				bool isCallableFromTasklet{ false };  // 41
				bool isLatent;                        // 42
				std::uint32_t userFlags{ 0 };         // 44
				BSFixedString docString;              // 48
			};
			static_assert(sizeof(NativeFunctionBase) == 0x50);
		}
	}
}
