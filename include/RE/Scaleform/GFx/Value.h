#pragma once

#include <cassert>

#include "RE/Scaleform/GFx/PlayerStats.h"
#include "RE/Scaleform/Render/Constants.h"
#include "RE/Scaleform/Render/Cxform.h"
#include "RE/Scaleform/Render/Matrix2x4.h"
#include "RE/Scaleform/Render/Matrix3x4.h"
#include "RE/Scaleform/Render/Matrix4x4.h"
#include "RE/Scaleform/Memory.h"
#include "RE/Scaleform/NewOverrideBase.h"


namespace RE
{
	namespace Scaleform
	{
		class String;


		namespace GFx
		{
			namespace AMP
			{
				class ViewStats;
			}


			class ASUserData;
			class MemberValueSet;
			class Movie;
			class MovieImpl;


			class Value
			{
			public:
				enum class ValueType : UInt32
				{
					kNone = 0,

					kUndefined = kNone,
					kNull = 0x01,
					kBoolean = 0x02,
					kInt = 0x03,
					kUInt = 0x04,
					kNumber = 0x05,
					kString = 0x06,
					kStringW = 0x07,
					kObject = 0x08,
					kArray = 0x09,
					kDisplayObject = 0x0A,	// stage instances (MovieClip, Button, etc.)
					kClosure = 0x0B,	// function closure object

					kOrphanedBit = 1 << 5,
					kManagedBit = 1 << 6,
					kConvertBit = 1 << 7,

					kTypeMask = kConvertBit | 0x0F,

					// indicates the result of SetVariable/Invoke should be converted to this type
					kConvertBoolean = kConvertBit | kBoolean,
					kConvertInt = kConvertBit | kInt,
					kConvertUInt = kConvertBit | kUInt,
					kConvertNumber = kConvertBit | kNumber,
					kConvertString = kConvertBit | kString,
					kConvertStringW = kConvertBit | kStringW
				};


				class DisplayInfo
				{
				public:
					enum class Flag : UInt16
					{
						kNone = 0,
						kX = 1 << 0,
						kY = 1 << 1,
						kRotation = 1 << 2,
						kXScale = 1 << 3,
						kYScale = 1 << 4,
						kAlpha = 1 << 5,
						kVisible = 1 << 6,
						kZ = 1 << 7,
						kXRotation = 1 << 8,
						kYRotation = 1 << 9,
						kZScale = 1 << 10,
						kFOV = 1 << 11,
						kProjMatrix3D = 1 << 12,
						kViewMatrix3D = 1 << 13,
						kEdgeAAMode = 1 << 14
					};


					DisplayInfo();
					DisplayInfo(double a_x, double a_y);
					DisplayInfo(double a_rotation);
					DisplayInfo(bool a_visible);

					void					Clear();
					void					Initialize(Flag a_varsSet, double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible, double a_z, double a_xRotation, double a_yRotation, double a_zScale, double a_fov, const Render::Matrix3F& a_viewM, const Render::Matrix4F& a_projM, Render::EdgeAAMode a_edgeAAMode);
					void					SetX(double a_x);
					void					SetY(double a_y);
					void					SetRotation(double a_degrees);
					void					SetXScale(double a_xScale);
					void					SetYScale(double a_yScale);
					void					SetAlpha(double a_alpha);
					void					SetVisible(bool a_visible);
					void					SetZ(double a_z);
					void					SetXRotation(double a_degrees);
					void					SetYRotation(double a_degrees);
					void					SetZScale(double a_zScale);
					void					SetFOV(double a_fov);
					void					SetProjectionMatrix3D(const Render::Matrix4F& a_matrix);
					void					ClearProjectionMatrix3D();
					void					SetViewMatrix3D(const Render::Matrix3F& a_matrix);
					void					ClearViewMatrix3D();
					void					SetEdgeAAMode(Render::EdgeAAMode a_edgeAAMode);
					void					SetPosition(double a_x, double a_y);
					void					SetScale(double a_xScale, double a_yScale);
					void					Set(double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible);
					void					Set(double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible, double a_z, double a_xRotation, double a_yRotation, double a_zScale);
					double					GetX() const;
					double					GetY() const;
					double					GetRotation() const;
					double					GetXScale() const;
					double					GetYScale() const;
					double					GetAlpha() const;
					bool					GetVisible() const;
					double					GetZ() const;
					double					GetXRotation() const;
					double					GetYRotation() const;
					double					GetZScale() const;
					double					GetFOV() const;
					const Render::Matrix4F&	GetProjectionMatrix3D() const;
					const Render::Matrix3F&	GetViewMatrix3D() const;
					Render::EdgeAAMode		GetEdgeAAMode() const;
					bool					IsFlagSet(Flag a_flag) const;

				protected:
					void	SetFlags(Flag a_flags);
					void	ClearFlags(Flag a_flags);


					// members
					double				_x;						// 00
					double				_y;						// 08
					double				_rotation;				// 10
					double				_xScale;				// 18
					double				_yScale;				// 20
					double				_alpha;					// 28
					bool				_visible;				// 30
					UInt8				_pad31;					// 31
					UInt16				_pad32;					// 32
					UInt32				_pad34;					// 34
					double				_z;						// 38
					double				_xRotation;				// 40
					double				_yRotation;				// 48
					double				_zScale;				// 50
					double				_fov;					// 58
					Render::Matrix3F	_viewMatrix3D;			// 60
					Render::Matrix4F	_projectionMatrix3D;	// 90
					Render::EdgeAAMode	_edgeAAMode;			// D0
					Flag				_varsSet;				// C4
					UInt16				_padC6;					// C6
					UInt64				_padC8;					// C8
				};
				STATIC_ASSERT(sizeof(DisplayInfo) == 0xE0);


				class ObjectInterface : public NewOverrideBase<kStatMV_Other_Mem>
				{
				public:
					class ObjVisitor
					{
					public:
						virtual ~ObjVisitor() = default;									// 00

						// add
						virtual bool	IncludeAS3PublicMembers() const;					// 01
						virtual void	Visit(const char* a_name, const Value& a_val) = 0;	// 02

						FO_HEAP_REDEFINE_NEW();
					};
					STATIC_ASSERT(sizeof(ObjVisitor) == 0x8);


					class ArrVisitor
					{
					public:
						inline static const void* RTTI = RTTI_Scaleform__GFx__Value__ObjectInterface__ArrVisitor;


						virtual ~ArrVisitor() = default;							// 00

						// add
						virtual void Visit(UInt32 a_idx, const Value& a_val) = 0;	// 01

						FO_HEAP_REDEFINE_NEW();
					};
					STATIC_ASSERT(sizeof(ArrVisitor) == 0x8);


					ObjectInterface(MovieImpl* a_movieRoot);
					virtual ~ObjectInterface() = default;																																				// 00

					virtual void			ObjectAddRef(Value* a_val, void* a_obj) = 0;																												// 01
					virtual void			ObjectRelease(Value* a_val, void* a_obj) = 0;																												// 02
					virtual bool			HasMember(void* a_data, const char* a_name, bool a_isDObj) const = 0;																						// 03
					virtual bool			GetMember(void* a_data, const char* a_name, Value* a_val, bool a_isDObj) const = 0;																			// 04
					virtual bool			SetMember(void* a_data, const char* a_name, const Value& a_value, bool a_isDObj) = 0;																		// 05
					virtual bool			Invoke(void* a_data, Value* a_result, const char* a_name, const Value* a_args, UPInt a_numArgs, bool a_isDObj) = 0;											// 06
					virtual bool			InvokeClosure(void* a_data, UPInt a_dataAux, Value* a_result, const Value* a_args, UPInt a_numArgs) = 0;													// 07
					virtual bool			DeleteMember(void* a_data, const char* name, bool a_isDObj) = 0;																							// 08
					virtual void			VisitMembers(void* a_data, ObjVisitor* a_visitor, bool a_isDObj) const = 0;																					// 09
					virtual UInt32			GetArraySize(void* a_data) const = 0;																														// 0A
					virtual bool			SetArraySize(void* a_data, UInt32 a_size) = 0;																												// 0B
					virtual bool			GetElement(void* a_data, UInt32 a_idx, Value* a_val) const = 0;																								// 0C
					virtual bool			SetElement(void* a_data, UInt32 a_idx, const Value& a_value) = 0;																							// 0D
					virtual void			VisitElements(void* a_data, ArrVisitor* a_visitor, UInt32 a_idx, SInt32 a_count) const = 0;																	// 0E
					virtual bool			PushBack(void* a_data, const Value& a_value) = 0;																											// 0F
					virtual bool			PopBack(void* a_data, Value* a_val) = 0;																													// 10
					virtual bool			RemoveElements(void* a_data, UInt32 a_idx, SInt32 a_count) = 0;																								// 11
					virtual bool			IsByteArray(void* a_data) const = 0;																														// 12
					virtual UInt32			GetByteArraySize(void* a_data) const = 0;																													// 13
					virtual bool			ReadFromByteArray(void* a_data, UInt8* a_destBuf, UPInt a_destBuffSize) const = 0;																			// 14
					virtual bool			WriteToByteArray(void* a_data, const UInt8* a_srcBuf, UPInt a_writeSize) = 0;																				// 15
					virtual bool			IsDisplayObjectActive(void* a_data) const = 0;																												// 16
					virtual bool			GetDisplayInfo(void* a_data, DisplayInfo* a_info) const = 0;																								// 17
					virtual bool			SetDisplayInfo(void* a_data, const DisplayInfo& a_info) = 0;																								// 18
					virtual bool			GetWorldMatrix(void* a_data, Render::Matrix2F* a_mat) const = 0;																							// 19
					virtual bool			GetDisplayMatrix(void* a_data, Render::Matrix2F* a_mat) const = 0;																							// 1A
					virtual bool			SetDisplayMatrix(void* a_data, const Render::Matrix2F& a_mat) = 0;																							// 1B
					virtual bool			GetMatrix3D(void* a_data, Render::Matrix3F* a_mat) const = 0;																								// 1C
					virtual bool			SetMatrix3D(void* a_data, const Render::Matrix3F& a_mat) = 0;																								// 1D
					virtual bool			GetCxform(void* a_data, Render::Cxform* a_cx) const = 0;																									// 1E
					virtual bool			SetCxform(void* a_data, const Render::Cxform& a_cx) = 0;																									// 1F
					virtual bool			GetText(void* a_data, Value* a_val, bool a_isHTML) const = 0;																								// 20
					virtual bool			SetText(void* a_data, const char* a_text, bool a_isHTML) = 0;																								// 21
					virtual bool			SetText(void* a_data, const wchar_t* a_text, bool a_isHTML) = 0;																							// 22
					virtual bool			CreateEmptyMovieClip(void* a_data, GFx::Value* a_mc, const char* a_instanceName, SInt32 a_depth) = 0;														// 23
					virtual bool			AttachMovie(void* a_data, GFx::Value* a_mc, const char* a_symbolName, const char* a_instanceName, SInt32 a_depth, const MemberValueSet* a_initArgs) = 0;	// 24
					virtual bool			GotoAndPlay(void* a_data, const char* a_frame, bool a_stop) = 0;																							// 25
					virtual bool			GotoAndPlay(void* a_data, UInt32 a_frame, bool a_stop) = 0;																									// 26
					virtual void			ToString(String* a_str, const GFx::Value& a_thisVal) const = 0;																								// 27
					virtual void			SetUserData(void* a_data, ASUserData* a_userData, bool a_isDObj) = 0;																						// 28
					virtual ASUserData*		GetUserData(void* a_data, bool a_isDObj) const = 0;																											// 29
					virtual bool			CreateObjectValue(Value* a_val, void* a_data, bool a_isDObj) = 0;																							// 2A
					virtual AMP::ViewStats*	GetAdvanceStats() const = 0;																																// 2B

					bool		IsSameContext(ObjectInterface* a_objInterface);
					MovieImpl*	GetMovieImpl() const;

				protected:
					MovieImpl* _movieRoot;	// 08
				};
				STATIC_ASSERT(sizeof(ObjectInterface) == 0x10);


				using ObjectVisitor = ObjectInterface::ObjVisitor;
				using ArrayVisitor = ObjectInterface::ArrVisitor;


				Value();
				Value(SInt32 a_val);
				Value(UInt32 a_val);
				Value(double a_val);
				Value(bool a_val);
				Value(const char* a_val);
				Value(const wchar_t* a_val);
				Value(const Value& a_val);
				Value(Value&& a_val);
				~Value();

				SF_MEMORY_REDEFINE_NEW(Value, kStatMV_Default);

				Value& operator=(const Value& a_rhs);
				Value& operator=(Value&& a_rhs);

				bool operator==(const GFx::Value& a_rhs) const;

				ValueType GetType() const;

				bool	IsUndefined() const;
				bool	IsNull() const;
				bool	IsBool() const;
				bool	IsInt() const;
				bool	IsUInt() const;
				bool	IsNumber() const;
				bool	IsNumeric() const;
				bool	IsString() const;
				bool	IsStringW() const;
				bool	IsObject() const;
				bool	IsArray() const;
				bool	IsDisplayObject() const;
				bool	IsClosure() const;
				bool	IsOrphaned() const;

				bool			GetBool() const;
				SInt32			GetInt() const;
				UInt32			GetUInt() const;
				double			GetNumber() const;
				const char*		GetString() const;
				const wchar_t*	GetStringW() const;
				void			SetUndefined();
				void			SetNull();
				void			SetBoolean(bool a_val);
				void			SetInt(SInt32 a_val);
				void			SetUInt(UInt32 a_val);
				void			SetNumber(double a_val);
				void			SetString(const char* a_val);
				void			SetStringW(const wchar_t* a_val);
				void			SetConvertBoolean();
				void			SetConvertNumber();
				void			SetConvertString();
				void			SetConvertStringW();


				// AS Object support
				// Valid for Object, Array, and DisplayObject types
				bool		HasMember(const char* a_name) const;
				bool		GetMember(const char* a_name, Value* a_val) const;
				bool		SetMember(const char* a_name, const Value& a_val);
				bool		Invoke(const char* a_name, Value* a_result, const Value* a_args, UPInt a_numArgs);
				bool		Invoke(const char* a_name, Value* a_result = 0);
				void		VisitMembers(ObjectVisitor* a_visitor) const;
				bool		DeleteMember(const char* a_name);
				void		SetUserData(ASUserData* a_data);
				ASUserData*	GetUserData() const;


				// AS3 Closure support
				// Valid for Closure type
				bool	InvokeSelf(Value* a_result, const Value* a_args, UPInt a_numArgs);
				bool	InvokeSelf(Value* a_result = 0);


				// AS Array support
				// Valid for Array type
				UInt32	GetArraySize() const;
				bool	SetArraySize(UInt32 a_size);
				bool	GetElement(UInt32 a_idx, Value* a_val) const;
				bool	SetElement(UInt32 a_idx, const Value& a_val);
				void	VisitElements(ArrayVisitor* a_visitor, UInt32 a_idx, SInt32 a_count = -1) const;
				void	VisitElements(ArrayVisitor* a_visitor) const;
				bool	PushBack(const Value& a_val);
				bool	PopBack(Value* a_val = 0);
				bool	RemoveElements(UInt32 a_idx, SInt32 a_count = -1);
				bool	RemoveElement(UInt32 a_idx);
				bool	ClearElements();


				// AS3 ByteArray support
				// Valid for ByteArray type
				bool	IsByteArray() const;
				UInt32	GetByteArraySize() const;
				bool	ReadFromByteArray(UInt8* a_destBuf, UPInt a_destBufSize);
				bool	WriteToByteArray(const UInt8* a_srcBuf, UPInt a_writeSize);


				// AS display object support
				// Valid for DisplayObject type
				bool	IsDisplayObjectActive() const;
				bool	GetDisplayInfo(DisplayInfo* a_info) const;
				bool	SetDisplayInfo(const DisplayInfo& a_info);
				bool	GetWorldMatrix(Render::Matrix2F* a_mat) const;
				bool	GetDisplayMatrix(Render::Matrix2F* a_mat) const;
				bool	SetDisplayMatrix(const Render::Matrix2F& a_mat);
				bool	GetMatrix3D(Render::Matrix3F* a_mat) const;
				bool	SetMatrix3D(const Render::Matrix3F& a_mat);
				bool	GetColorTransform(Render::Cxform* a_cx) const;
				bool	SetColorTransform(Render::Cxform& a_cx);


				// AS TextField support
				// Valid for DisplayObject type
				bool	SetText(const char* a_text);
				bool	SetText(const wchar_t* a_text);
				bool	SetTextHTML(const char* a_html);
				bool	SetTextHTML(const wchar_t* a_html);
				bool	GetText(Value* a_val) const;
				bool	GetTextHTML(Value* a_val) const;


				// AS MovieClip support
				// Valid for DisplayObject type
				bool	CreateEmptyMovieClip(GFx::Value* a_mc, const char* a_instanceName, SInt32 a_depth = -1);
				bool	AttachMovie(GFx::Value* a_mc, const char* a_symbolName, const char* a_instanceName, SInt32 a_depth = -1, const MemberValueSet* a_initArgs = 0);
				bool	GotoAndPlay(const char* a_frame);
				bool	GotoAndStop(const char* a_frame);
				bool	GotoAndPlay(UInt32 a_frame);
				bool	GotoAndStop(UInt32 a_frame);
				Movie*	GetMovie() const;

			protected:
				union ValueUnion
				{
					ValueUnion();


					SInt32			signedInt;
					UInt32			unsignedInt;
					double			number;
					bool			boolean;
					const char*		string;
					const char**	stringManaged;
					const wchar_t*	stringW;
					void*			data;
				};
				STATIC_ASSERT(sizeof(ValueUnion) == 0x8);


				bool	IsManagedValue() const;
				void	ChangeType(ValueType a_type);
				void	AcquireManagedValue(const Value& a_src);
				void	ReleaseManagedValue();


				ObjectInterface*	_objectInterface;	// 00
				ValueType			_type;				// 08
				UInt32				_pad0C;				// 0C
				ValueUnion			_value;				// 10
				UPInt				_dataAux;			// 18
			};
			STATIC_ASSERT(sizeof(Value) == 0x20);
		}
	}
}
