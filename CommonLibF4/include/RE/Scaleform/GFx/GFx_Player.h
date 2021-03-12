#pragma once

#include "RE/Scaleform/GFx/GFx_Loader.h"
#include "RE/Scaleform/GFx/GFx_Log.h"
#include "RE/Scaleform/GFx/GFx_Types.h"
#include "RE/Scaleform/Kernel/SF_RefCount.h"
#include "RE/Scaleform/Render/Render_Constants.h"
#include "RE/Scaleform/Render/Render_Context.h"
#include "RE/Scaleform/Render/Render_TreeNode.h"
#include "RE/Scaleform/Render/Render_Viewport.h"

namespace RE::Scaleform::GFx
{
	class ASMovieRootBase;
	class FunctionHandler;
	class MemoryContext;
	class Movie;
	class MovieDef;
	class MovieImpl;
	class Value;
	class Viewport;

	struct MemoryParams;

	class Viewport :
		public Render::Viewport
	{
	public:
		// members
		float scale;        // 2C
		float aspectRatio;  // 30
	};
	static_assert(sizeof(Viewport) == 0x34);

	class __declspec(novtable) MemoryContext :
		public RefCountBase<MemoryContext, 2>  // 00
	{
	public:
		virtual ~MemoryContext() = default;
	};
	static_assert(sizeof(MemoryContext) == 0x10);

	struct MemoryParams
	{
	public:
		// members
		MemoryHeap::HeapDesc desc;                                                 // 00
		float heapLimitMultiplier{ 0.25F };                                        // 40
		std::uint32_t maxCollectionRoots{ static_cast<std::uint32_t>(-1) };        // 44
		std::uint32_t framesBetweenCollections{ static_cast<std::uint32_t>(-1) };  // 48
		std::uint32_t initialDynamicLimit{ static_cast<std::uint32_t>(-1) };       // 4C
		std::uint32_t runsToUpgradeGen{ static_cast<std::uint32_t>(-1) };          // 50
		std::uint32_t runsToCollectYoung{ static_cast<std::uint32_t>(-1) };        // 54
		std::uint32_t runsToCollectOld{ static_cast<std::uint32_t>(-1) };          // 58
	};
	static_assert(sizeof(MemoryParams) == 0x60);

	class __declspec(novtable) MovieDef :
		public Resource,  // 00
		public StateBag   // 18
	{
	public:
		enum class FileAttrFlags : std::uint32_t
		{
			kUseNetwork = 1 << 0,
			kUseActionScript3 = 1 << 3,
			kHasMetadata = 1 << 4
		};

		enum class VisitResourceMask : std::uint32_t
		{
			kNestedMovies = 1 << 15,

			kFonts = 1 << 0,
			kBitmaps = 1 << 1,
			kGradientImages = 1 << 2,
			kEditTextFields = 1 << 3,
			kSounds = 1 << 4,
			kSprite = 1 << 5,

			kAllLocalImages = (kBitmaps | kGradientImages),
			kAllImages = (kBitmaps | kGradientImages | kNestedMovies)
		};

		struct __declspec(novtable) ImportVisitor
		{
		public:
			virtual ~ImportVisitor() = default;  // 00

			// add
			virtual void Visit(MovieDef* a_parentDef, MovieDef* a_importDef, const char* a_importedMovieFilename) = 0;  // 01
		};
		static_assert(sizeof(ImportVisitor) == 0x8);

		struct __declspec(novtable) ResourceVisitor :
			public FileTypeConstants  // 00
		{
		public:
			virtual ~ResourceVisitor() = default;  // 00

			// add
			virtual void Visit(MovieDef* a_movieDef, Resource* a_resource, ResourceId a_rid, const char* a_exportName) = 0;  // 01
		};
		static_assert(sizeof(ResourceVisitor) == 0x8);

		// add
		virtual std::uint32_t GetVersion() const = 0;                                                                                                                              // 04
		virtual std::uint32_t GetLoadingFrame() const = 0;                                                                                                                         // 05
		virtual float GetWidth() const = 0;                                                                                                                                        // 06
		virtual float GetHeight() const = 0;                                                                                                                                       // 07
		virtual std::uint32_t GetFrameCount() const = 0;                                                                                                                           // 08
		virtual float GetFrameRate() const = 0;                                                                                                                                    // 09
		virtual RectF GetFrameRect() const = 0;                                                                                                                                    // 0A
		virtual std::uint32_t GetSWFFlags() const = 0;                                                                                                                             // 0B
		virtual const char* GetFileURL() const = 0;                                                                                                                                // 0C
		virtual void WaitForLoadFinish(bool a_cancel = false) const = 0;                                                                                                           // 0D
		virtual void WaitForFrame(std::uint32_t a_frame) const = 0;                                                                                                                // 0E
		virtual FileAttrFlags GetFileAttributes() const = 0;                                                                                                                       // 0F
		virtual std::uint32_t GetMetadata(char* a_buff, std::uint32_t a_buffSize) const = 0;                                                                                       // 10
		virtual MemoryHeap* GetLoadDataHeap() const = 0;                                                                                                                           // 11
		virtual MemoryHeap* GetBindDataHeap() const = 0;                                                                                                                           // 12
		virtual MemoryHeap* GetImageHeap() const = 0;                                                                                                                              // 13
		virtual Resource* GetMovieDataResource() const = 0;                                                                                                                        // 14
		virtual const ExporterInfo* GetExporterInfo() const = 0;                                                                                                                   // 15
		virtual MemoryContext* CreateMemoryContext(const char* a_heapName, const MemoryParams& a_memParams, bool a_debugHeap) = 0;                                                 // 16
		virtual Movie* CreateInstance(const MemoryParams& a_memParams, bool a_initFirstFrame, ActionControl* a_actionControl, Render::ThreadCommandQueue* a_queue = nullptr) = 0;  // 18
		virtual Movie* CreateInstance(MemoryContext* a_memContext, bool a_initFirstFrame, ActionControl* a_actionControl, Render::ThreadCommandQueue* a_queue = nullptr) = 0;      // 17
		virtual void VisitImportedMovies(ImportVisitor* a_visitor) = 0;                                                                                                            // 19
		virtual void VisitResources(ResourceVisitor* a_visitor, VisitResourceMask a_visitMask = VisitResourceMask::kAllImages) = 0;                                                // 1A
		virtual Resource* GetResource(const char* a_exportName) const = 0;                                                                                                         // 1B

		[[nodiscard]] Movie* CreateInstance(
			bool a_initFirstFrame = false,
			std::size_t a_memoryArena = 0,
			ActionControl* a_actionControl = nullptr,
			Render::ThreadCommandQueue* a_queue = nullptr)
		{
			MemoryParams memParams;
			memParams.desc.arena = a_memoryArena;
			return CreateInstance(memParams, a_initFirstFrame, a_actionControl, a_queue);
		}
	};
	static_assert(sizeof(MovieDef) == 0x20);

	class Value
	{
	public:
		enum class ValueType : std::int32_t
		{
			kUndefined,
			kNull,
			kBoolean,
			kInt,
			kUInt,
			kNumber,
			kString,

			kStringW,

			kObject,
			kArray,
			kDisplayObject,
			kClosure,

			kOrphanedBit = 1 << 5,
			kManagedBit = 1 << 6,
			kConvertBit = 1 << 7,

			kTypeMask = kConvertBit | 0x0F,

			kConvertBoolean = kConvertBit | kBoolean,
			kConvertInt = kConvertBit | kInt,
			kConvertUInt = kConvertBit | kUInt,
			kConvertNumber = kConvertBit | kNumber,
			kConvertString = kConvertBit | kString,
			kConvertStringW = kConvertBit | kStringW
		};

		union ValueUnion
		{
			ValueUnion() noexcept :
				data(nullptr)
			{}

			ValueUnion(const ValueUnion& a_rhs) noexcept :
				data(a_rhs.data)
			{}

			ValueUnion(ValueUnion&& a_rhs) noexcept :
				data(a_rhs.data)
			{
				a_rhs.data = nullptr;
			}

			explicit ValueUnion(std::int32_t a_rhs) noexcept :
				int32(a_rhs)
			{}

			explicit ValueUnion(std::uint32_t a_rhs) noexcept :
				uint32(a_rhs)
			{}

			explicit ValueUnion(double a_rhs) noexcept :
				number(a_rhs)
			{}

			explicit ValueUnion(bool a_rhs) noexcept :
				boolean(a_rhs)
			{}

			explicit ValueUnion(const char* a_rhs) noexcept :
				string(a_rhs)
			{}

			explicit ValueUnion(const wchar_t* a_rhs) noexcept :
				wstring(a_rhs)
			{}

			ValueUnion& operator=(const ValueUnion& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					data = a_rhs.data;
				}
				return *this;
			}

			ValueUnion& operator=(ValueUnion&& a_rhs) noexcept
			{
				if (this != std::addressof(a_rhs)) {
					data = a_rhs.data;
					a_rhs.data = nullptr;
				}
				return *this;
			}

			ValueUnion& operator=(std::int32_t a_rhs) noexcept
			{
				int32 = a_rhs;
				return *this;
			}

			ValueUnion& operator=(std::uint32_t a_rhs) noexcept
			{
				uint32 = a_rhs;
				return *this;
			}

			ValueUnion& operator=(double a_rhs) noexcept
			{
				number = a_rhs;
				return *this;
			}

			ValueUnion& operator=(bool a_rhs) noexcept
			{
				boolean = a_rhs;
				return *this;
			}

			ValueUnion& operator=(const char* a_rhs) noexcept
			{
				string = a_rhs;
				return *this;
			}

			ValueUnion& operator=(const wchar_t* a_rhs) noexcept
			{
				wstring = a_rhs;
				return *this;
			}

			std::int32_t int32;
			std::uint32_t uint32;
			double number;
			bool boolean;
			const char* string;
			const char** mstring;
			const wchar_t* wstring;
			void* data;
		};
		static_assert(sizeof(ValueUnion) == 0x8);

		class __declspec(novtable) ObjectInterface :
			public NewOverrideBase<327>
		{
		public:
			class __declspec(novtable) ObjVisitor
			{
			public:
				virtual ~ObjVisitor() = default;  // 00

				// add
				virtual bool IncludeAS3PublicMembers() const { return false; }   // 01
				virtual void Visit(const char* a_name, const Value& a_val) = 0;  // 02
			};
			static_assert(sizeof(ObjVisitor) == 0x8);

			class __declspec(novtable) ArrVisitor
			{
			public:
				virtual ~ArrVisitor() = default;

				// add
				virtual void Visit(std::uint32_t a_idx, const Value& a_val) = 0;  // 00
			};
			static_assert(sizeof(ArrVisitor) == 0x8);

			virtual ~ObjectInterface() = default;  // 00

			void ObjectAddRef(Value* a_val, void* a_obj)
			{
				using func_t = decltype(&ObjectInterface::ObjectRelease);
				REL::Relocation<func_t> func{ REL::ID(244786) };
				return func(this, a_val, a_obj);
			}

			void ObjectRelease(Value* a_val, void* a_obj)
			{
				using func_t = decltype(&ObjectInterface::ObjectRelease);
				REL::Relocation<func_t> func{ REL::ID(856221) };
				return func(this, a_val, a_obj);
			}

			bool HasMember(void* a_data, const char* a_name, bool a_isdobj) const
			{
				using func_t = decltype(&ObjectInterface::HasMember);
				REL::Relocation<func_t> func{ REL::ID(788691) };
				return func(this, a_data, a_name, a_isdobj);
			}

			bool GetMember(void* a_data, const char* a_name, Value* a_val, bool a_isdobj) const
			{
				using func_t = decltype(&ObjectInterface::GetMember);
				REL::Relocation<func_t> func{ REL::ID(1517430) };
				return func(this, a_data, a_name, a_val, a_isdobj);
			}

			bool SetMember(void* a_data, const char* a_name, const Value& a_value, bool a_isdobj)
			{
				using func_t = decltype(&ObjectInterface::SetMember);
				REL::Relocation<func_t> func{ REL::ID(1360149) };
				return func(this, a_data, a_name, a_value, a_isdobj);
			}

			bool Invoke(void* a_data, Value* a_result, const char* a_name, const Value* a_args, std::size_t a_numArgs, bool a_isdobj)
			{
				using func_t = decltype(&ObjectInterface::Invoke);
				REL::Relocation<func_t> func{ REL::ID(655847) };
				return func(this, a_data, a_result, a_name, a_args, a_numArgs, a_isdobj);
			}

			bool PushBack(void* a_data, const Value& a_value)
			{
				using func_t = decltype(&ObjectInterface::PushBack);
				REL::Relocation<func_t> func{ REL::ID(1330475) };
				return func(this, a_data, a_value);
			}

			// members
			MovieImpl* movieRoot;  // 08
		};
		static_assert(sizeof(ObjectInterface) == 0x10);

		Value() noexcept = default;

		Value(const Value& a_rhs) :
			_type(a_rhs._type),
			_value(a_rhs._value),
			_dataAux(a_rhs._dataAux)
		{
			if (a_rhs.IsManagedValue()) {
				AcquireManagedValue(a_rhs);
			}
		}

		Value(Value&& a_rhs) noexcept :
			_objectInterface(a_rhs._objectInterface),
			_type(a_rhs._type),
			_value(std::move(a_rhs._value)),
			_dataAux(a_rhs._dataAux)
		{
			a_rhs._objectInterface = nullptr;
			a_rhs._type = ValueType::kUndefined;
			a_rhs._dataAux = 0;
		}

		Value(std::nullptr_t) noexcept :
			_type(ValueType::kNull)
		{}

		Value(std::int32_t a_rhs) noexcept :
			_type(ValueType::kInt),
			_value(a_rhs)
		{}

		Value(std::uint32_t a_rhs) noexcept :
			_type(ValueType::kUInt),
			_value(a_rhs)
		{}

		Value(double a_rhs) noexcept :
			_type(ValueType::kNumber),
			_value(a_rhs)
		{}

		Value(bool a_rhs) noexcept :
			_type(ValueType::kBoolean),
			_value(a_rhs)
		{}

		Value(const char* a_rhs) noexcept :
			_type(ValueType::kString),
			_value(a_rhs)
		{}

		Value(const wchar_t* a_rhs) noexcept :
			_type(ValueType::kStringW),
			_value(a_rhs)
		{}

		~Value()
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kUndefined;
		}

		Value& operator=(const Value& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				if (IsManagedValue()) {
					ReleaseManagedValue();
				}

				_type = a_rhs._type;
				_value = a_rhs._value;
				_dataAux = a_rhs._dataAux;

				if (a_rhs.IsManagedValue()) {
					AcquireManagedValue(a_rhs);
				}
			}
			return *this;
		}

		Value& operator=(Value&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				if (IsManagedValue()) {
					ReleaseManagedValue();
				}

				_objectInterface = a_rhs._objectInterface;
				a_rhs._objectInterface = nullptr;

				_type = a_rhs._type;
				a_rhs._type = ValueType::kUndefined;

				_value = std::move(a_rhs._value);

				_dataAux = a_rhs._dataAux;
				a_rhs._dataAux = 0;
			}
			return *this;
		}

		Value& operator=(std::nullptr_t) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kNull;
			return *this;
		}

		Value& operator=(std::int32_t a_rhs) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kInt;
			_value = a_rhs;
			return *this;
		}

		Value& operator=(std::uint32_t a_rhs) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kUInt;
			_value = a_rhs;
			return *this;
		}

		Value& operator=(double a_rhs) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kNumber;
			_value = a_rhs;
			return *this;
		}

		Value& operator=(bool a_rhs) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kBoolean;
			_value = a_rhs;
			return *this;
		}

		Value& operator=(const char* a_rhs) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kString;
			_value = a_rhs;
			return *this;
		}

		Value& operator=(const wchar_t* a_rhs) noexcept
		{
			if (IsManagedValue()) {
				ReleaseManagedValue();
			}

			_type = ValueType::kStringW;
			_value = a_rhs;
			return *this;
		}

		[[nodiscard]] ValueType GetType() const noexcept { return *(_type & ValueType::kTypeMask); }

		[[nodiscard]] bool IsArray() const noexcept { return GetType() == ValueType::kArray; }
		[[nodiscard]] bool IsBoolean() const noexcept { return GetType() == ValueType::kBoolean; }
		[[nodiscard]] bool IsDisplayObject() const noexcept { return GetType() == ValueType::kDisplayObject; }
		[[nodiscard]] bool IsInt() const noexcept { return GetType() == ValueType::kInt; }
		[[nodiscard]] bool IsNumber() const noexcept { return GetType() == ValueType::kNumber; }

		[[nodiscard]] bool IsObject() const noexcept
		{
			switch (GetType()) {
			case ValueType::kObject:
			case ValueType::kArray:
			case ValueType::kDisplayObject:
				return true;
			default:
				return false;
			}
		}

		[[nodiscard]] bool IsString() const noexcept { return GetType() == ValueType::kString; }
		[[nodiscard]] bool IsUndefined() const noexcept { return GetType() == ValueType::kUndefined; }
		[[nodiscard]] bool IsUInt() const noexcept { return GetType() == ValueType::kUInt; }

		[[nodiscard]] double GetNumber() const
		{
			assert(IsNumber());
			return _value.number;
		}

		[[nodiscard]] std::string_view GetString() const
		{
			assert(IsString());
			return IsManagedValue() ?
                       *_value.mstring :
                       _value.string;
		}

		bool HasMember(stl::zstring a_name) const
		{
			assert(IsObject());
			return _objectInterface->HasMember(_value.data, a_name.data(), IsDisplayObject());
		}

		bool GetMember(stl::zstring a_name, Value* a_val) const
		{
			assert(IsObject());
			return _objectInterface->GetMember(_value.data, a_name.data(), a_val, IsDisplayObject());
		}

		bool SetMember(stl::zstring a_name, const Value& a_val)
		{
			assert(IsObject());
			return _objectInterface->SetMember(_value.data, a_name.data(), a_val, IsDisplayObject());
		}

		bool Invoke(const char* a_name, Value* a_result, const Value* a_args, std::size_t a_numArgs)
		{
			assert(IsObject());
			return _objectInterface->Invoke(_value.data, a_result, a_name, a_args, a_numArgs, IsDisplayObject());
		}

		bool Invoke(const char* a_name, Value* a_result = nullptr)
		{
			return Invoke(a_name, a_result, nullptr, 0);
		}

		bool PushBack(const Value& a_val)
		{
			assert(IsArray());
			return _objectInterface->PushBack(_value.data, a_val);
		}

	private:
		void AcquireManagedValue(const Value& a_rhs)
		{
			assert(a_rhs._value.data && a_rhs._objectInterface);
			_objectInterface = a_rhs._objectInterface;
			_objectInterface->ObjectAddRef(this, _value.data);
		}

		[[nodiscard]] bool IsManagedValue() const noexcept
		{
			const auto managed = _type.all(ValueType::kManagedBit);
			assert(managed ? _objectInterface != nullptr : true);
			return managed;
		}

		void ReleaseManagedValue()
		{
			assert(_value.data && _objectInterface);
			_objectInterface->ObjectRelease(this, _value.data);
			_objectInterface = nullptr;
		}

		// members
		ObjectInterface* _objectInterface{ nullptr };                              // 00
		stl::enumeration<ValueType, std::int32_t> _type{ ValueType::kUndefined };  // 08
		ValueUnion _value{};                                                       // 10
		std::size_t _dataAux{ 0 };                                                 // 18
	};
	static_assert(sizeof(Value) == 0x20);

	class __declspec(novtable) FunctionHandler :
		public RefCountBase<FunctionHandler, 2>  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::Scaleform__GFx__FunctionHandler };
		static constexpr auto VTABLE{ VTABLE::Scaleform__GFx__FunctionHandler };

		struct Params
		{
		public:
			// members
			Value* retVal;           // 00
			Movie* movie;            // 08
			Value* self;             // 10
			Value* argsWithThisRef;  // 18
			Value* args;             // 20
			std::uint32_t argCount;  // 28
			void* userData;          // 30
		};
		static_assert(sizeof(Params) == 0x38);

		virtual ~FunctionHandler() = default;  // 00

		// add
		virtual void Call(const Params& a_params) = 0;  // 01
	};
	static_assert(sizeof(FunctionHandler) == 0x10);

	using MovieDisplayHandle = Render::DisplayHandle<Render::TreeRoot>;

	class __declspec(novtable) Movie :
		public RefCountBase<Movie, 327>,  // 00
		public StateBag                   // 10
	{
	public:
		enum class SetVarType : std::int32_t
		{
			kNormal,
			kSticky,
			kPermanent
		};

		enum class SetArrayType : std::int32_t
		{
			kInt,
			kDouble,
			kFloat,
			kString,
			kStringW,
			kValue
		};

		enum class ScaleModeType : std::int32_t
		{
			kNoScale,
			kShowAll,
			kExactFit,
			kNoBorder
		};

		enum class AlignType : std::int32_t
		{
			kCenter,
			kTopCenter,
			kBottomCenter,
			kCenterLeft,
			kCenterRight,
			kTopLeft,
			kTopRight,
			kBottomLeft,
			kBottomRight
		};

		enum HE_ReturnValueType
		{
			HE_NotHandled = 0,
			HE_Handled = 1,
			HE_NoDefaultAction = 2,
			HE_Completed = (HE_Handled | HE_NoDefaultAction)
		};

		enum class HitTestType : std::int32_t
		{
			kBounds = 0,
			kShapes = 1,
			kButtonEvents = 2,
			kShapesNoInvisible = 3
		};

		enum class ReportFlags : std::uint32_t
		{
			kNone = 0,
			kShortFileNames = 1 << 0,
			kNoCircularReferences = 1 << 1,
			kSuppressOverallStats = 1 << 2,
			kAddressesForAnonymObjsOnly = 1 << 3,
			kSuppressMovieDefsStats = 1 << 4,
			kNoEllipsis = 1 << 5
		};

		enum class MakeAllVisibleFlags : std::uint32_t
		{
			kNone = 0,
			kDontScaleDown = 1 << 0,
			kScaleUp50 = 1 << 1,
			kLeftTopToZero = 1 << 2
		};

		virtual MovieDef* GetMovieDef() const = 0;                                                                                                                       // 01
		virtual std::uint32_t GetCurrentFrame() const = 0;                                                                                                               // 02
		virtual bool HasLooped() const = 0;                                                                                                                              // 03
		virtual void GotoFrame(std::uint32_t a_frameNumber) = 0;                                                                                                         // 04
		virtual bool GotoLabeledFrame(const char* a_label, std::int32_t a_offset = 0) = 0;                                                                               // 05
		virtual void SetPlayState(PlayState a_state) = 0;                                                                                                                // 06
		virtual PlayState GetPlayState() const = 0;                                                                                                                      // 07
		virtual bool IsValid() = 0;                                                                                                                                      // 08
		virtual void SetVisible(bool a_visible) = 0;                                                                                                                     // 09
		virtual bool GetVisible() const = 0;                                                                                                                             // 0A
		virtual std::uint64_t GetASTimerMs() const = 0;                                                                                                                  // 0B
		virtual void SetViewport(const Viewport& a_viewDesc) = 0;                                                                                                        // 0C
		virtual void GetViewport(Viewport* a_viewDesc) const = 0;                                                                                                        // 0D
		virtual void SetViewScaleMode(ScaleModeType) = 0;                                                                                                                // 0E
		virtual ScaleModeType GetViewScaleMode() const = 0;                                                                                                              // 0F
		virtual void SetViewAlignment(AlignType) = 0;                                                                                                                    // 10
		virtual AlignType GetViewAlignment() const = 0;                                                                                                                  // 11
		virtual RectF GetVisibleFrameRect() const = 0;                                                                                                                   // 12
		virtual RectF GetSafeRect() const = 0;                                                                                                                           // 13
		virtual void SetSafeRect(const RectF& a_rect) = 0;                                                                                                               // 14
		virtual void SetEdgeAAMode(Render::EdgeAAMode a_edgeAA) = 0;                                                                                                     // 15
		virtual Render::EdgeAAMode GetEdgeAAMode() const = 0;                                                                                                            // 16
		virtual void Restart(bool a_advance0 = true) = 0;                                                                                                                // 17
		virtual float Advance(float a_deltaT, std::uint32_t a_frameCatchUpCount = 2, bool a_capture = true) = 0;                                                         // 18
		virtual void Capture(bool a_onChangeOnly = true) = 0;                                                                                                            // 19
		virtual const MovieDisplayHandle& GetDisplayHandle() const = 0;                                                                                                  // 1A
		virtual void SetCaptureThread(ThreadId a_captureThreadId) = 0;                                                                                                   // 1B
		virtual void ShutdownRendering(bool a_wait) = 0;                                                                                                                 // 1C
		virtual bool IsShutdownRenderingComplete() const = 0;                                                                                                            // 1D
		virtual void SetPause(bool a_pause) = 0;                                                                                                                         // 1E
		virtual bool IsPaused() const = 0;                                                                                                                               // 1F
		virtual void SetBackgroundColor(Render::Color a_bgColor) = 0;                                                                                                    // 20
		virtual void SetBackgroundAlpha(float a_alpha) = 0;                                                                                                              // 21
		virtual float GetBackgroundAlpha() const = 0;                                                                                                                    // 22
		virtual std::uint32_t HandleEvent(const Event& a_event) = 0;                                                                                                     // 23
		virtual void GetMouseState(std::uint32_t a_mouseIndex, float* a_x, float* a_y, std::uint32_t* a_buttons) = 0;                                                    // 24
		virtual void NotifyMouseState(float a_x, float a_y, std::uint32_t a_buttons, std::uint32_t a_mouseIndex = 0) = 0;                                                // 25
		virtual bool HitTest(float a_x, float a_y, HitTestType a_testCond = HitTestType::kShapes, std::uint32_t a_controllerIdx = 0) = 0;                                // 26
		virtual void* GetUserData() const = 0;                                                                                                                           // 27
		virtual void SetUserData(void*) = 0;                                                                                                                             // 28
		virtual bool IsMovieFocused() const = 0;                                                                                                                         // 29
		virtual bool GetDirtyFlag(bool a_doReset = true) = 0;                                                                                                            // 2A
		virtual void SetMouseCursorCount(std::uint32_t a_num) = 0;                                                                                                       // 2B
		virtual std::uint32_t GetMouseCursorCount() const = 0;                                                                                                           // 2C
		virtual void SetControllerCount(std::uint32_t a_num) = 0;                                                                                                        // 2D
		virtual std::uint32_t GetControllerCount() const = 0;                                                                                                            // 2E
		virtual void GetStats(StatBag* a_bag, bool a_reset = true) = 0;                                                                                                  // 2F
		virtual MemoryHeap* GetHeap() const = 0;                                                                                                                         // 30
		virtual void ForceCollectGarbage() = 0;                                                                                                                          // 31
		virtual void SuspendGC(bool a_suspend) = 0;                                                                                                                      // 32
		virtual void ScheduleGC() = 0;                                                                                                                                   // 33
		virtual void PrintObjectsReport(ReportFlags a_flags = ReportFlags::kNone, Log* a_log = nullptr, const char* a_swfName = nullptr) = 0;                            // 34
		virtual Render::PointF TranslateToScreen(const Render::PointF& a_pt, Matrix2F* a_userMatrix = nullptr) = 0;                                                      // 36
		virtual RectF TranslateToScreen(const RectF& a_pt, Matrix2F* a_userMatrix = nullptr) = 0;                                                                        // 35
		virtual bool TranslateLocalToScreen(const char* a_pathToCharacter, const Render::PointF& a_pt, Render::PointF* a_presPt, Matrix2F* a_userMatrix = nullptr) = 0;  // 37
		virtual bool SetControllerFocusGroup(std::uint32_t a_controllerIdx, std::uint32_t a_focusGroupIndex) = 0;                                                        // 38
		virtual std::uint32_t GetControllerFocusGroup(std::uint32_t a_controllerIdx) const = 0;                                                                          // 39
		virtual void ResetInputFocus(std::uint32_t a_controllerIdx) = 0;                                                                                                 // 3A
		virtual bool IsExitRequested() const = 0;                                                                                                                        // 3B
		virtual void GetViewMatrix3D(Matrix3F*) = 0;                                                                                                                     // 3C
		virtual void SetViewMatrix3D(const Matrix3F& a_matrix) = 0;                                                                                                      // 3D
		virtual void GetProjectionMatrix3D(Matrix4F*) = 0;                                                                                                               // 3E
		virtual void SetProjectionMatrix3D(const Matrix4F& a_matrix) = 0;                                                                                                // 3F
		virtual void SetStageAutoOrients(bool a_value = true) = 0;                                                                                                       // 40
		virtual void ForceUpdateImages() = 0;                                                                                                                            // 41
		virtual void MakeAreaVisible(const Render::RectF& a_screenRect, const Render::RectF& a_box, MakeAllVisibleFlags a_flags = MakeAllVisibleFlags::kNone) = 0;       // 42
		virtual void RestoreViewport() = 0;                                                                                                                              // 43

		void CreateFunction(Value* a_value, FunctionHandler* a_function, void* a_userData = nullptr);
		bool GetVariable(Value* a_val, const char* a_pathToVar) const;

		void Release()
		{
			using func_t = decltype(&Movie::Release);
			REL::Relocation<func_t> func{ REL::ID(404814) };
			return func(this);
		}

		// members
		Ptr<ASMovieRootBase> asMovieRoot;  // 18
	};
	static_assert(sizeof(Movie) == 0x20);
}
