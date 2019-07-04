#include "RE/Scaleform/GFx/Value.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			Value::DisplayInfo::DisplayInfo() :
				_x(0.0),
				_y(0.0),
				_rotation(0.0),
				_xScale(0.0),
				_yScale(0.0),
				_alpha(0.0),
				_visible(false),
				_pad31(0),
				_pad32(0),
				_pad34(0),
				_z(0.0),
				_xRotation(0.0),
				_yRotation(0.0),
				_zScale(0.0),
				_fov(0.0),
				_viewMatrix3D(),
				_projectionMatrix3D(),
				_edgeAAMode(Render::EdgeAAMode::kInherit),
				_varsSet(Flag::kNone),
				_padC6(0),
				_padC8(0)
			{}


			Value::DisplayInfo::DisplayInfo(double a_x, double a_y) :
				_x(a_x),
				_y(a_y),
				_rotation(0.0),
				_xScale(0.0),
				_yScale(0.0),
				_alpha(0.0),
				_visible(false),
				_pad31(0),
				_pad32(0),
				_pad34(0),
				_z(0.0),
				_xRotation(0.0),
				_yRotation(0.0),
				_zScale(0.0),
				_fov(0.0),
				_viewMatrix3D(),
				_projectionMatrix3D(),
				_edgeAAMode(Render::EdgeAAMode::kInherit),
				_varsSet(Flag::kX | Flag::kY),
				_padC6(0),
				_padC8(0)
			{}


			Value::DisplayInfo::DisplayInfo(double a_rotation) :
				_x(0.0),
				_y(0.0),
				_rotation(a_rotation),
				_xScale(0.0),
				_yScale(0.0),
				_alpha(0.0),
				_visible(false),
				_pad31(0),
				_pad32(0),
				_pad34(0),
				_z(0.0),
				_xRotation(0.0),
				_yRotation(0.0),
				_zScale(0.0),
				_fov(0.0),
				_viewMatrix3D(),
				_projectionMatrix3D(),
				_edgeAAMode(Render::EdgeAAMode::kInherit),
				_varsSet(Flag::kRotation),
				_padC6(0),
				_padC8(0)
			{}


			Value::DisplayInfo::DisplayInfo(bool a_visible) :
				_x(0.0),
				_y(0.0),
				_rotation(0.0),
				_xScale(0.0),
				_yScale(0.0),
				_alpha(0.0),
				_visible(a_visible),
				_pad31(0),
				_pad32(0),
				_pad34(0),
				_z(0.0),
				_xRotation(0.0),
				_yRotation(0.0),
				_zScale(0.0),
				_fov(0.0),
				_viewMatrix3D(),
				_projectionMatrix3D(),
				_edgeAAMode(Render::EdgeAAMode::kInherit),
				_varsSet(Flag::kVisible),
				_padC6(0),
				_padC8(0)
			{}


			void Value::DisplayInfo::Clear()
			{
				_varsSet = Flag::kNone;
			}


			void Value::DisplayInfo::Initialize(Flag a_varsSet, double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible, double a_z, double a_xRotation, double a_yRotation, double a_zScale, double a_fov, const Render::Matrix3F& a_viewM, const Render::Matrix4F& a_projM, Render::EdgeAAMode a_edgeAAMode)
			{
				_varsSet = a_varsSet;
				_x = a_x;
				_y = a_y;
				_rotation = a_rotation;
				_xScale = a_xScale;
				_yScale = a_yScale;
				_alpha = a_alpha;
				_visible = a_visible;
				_z = a_z;
				_xRotation = a_xRotation;
				_yRotation = a_yRotation;
				_zScale = a_zScale;
				_fov = a_fov;
				_viewMatrix3D = a_viewM;
				_projectionMatrix3D = a_projM;
				_edgeAAMode = a_edgeAAMode;
			}


			void Value::DisplayInfo::SetX(double a_x)
			{
				_x = a_x;
				SetFlags(Flag::kX);
			}


			void Value::DisplayInfo::SetY(double a_y)
			{
				_y = a_y;
				SetFlags(Flag::kY);
			}


			void Value::DisplayInfo::SetRotation(double a_degrees)
			{
				_rotation = a_degrees;
				SetFlags(Flag::kRotation);
			}


			void Value::DisplayInfo::SetXScale(double a_xScale)
			{
				_xScale = a_xScale;
				SetFlags(Flag::kXScale);
			}


			void Value::DisplayInfo::SetYScale(double a_yScale)
			{
				_yScale = a_yScale;
				SetFlags(Flag::kYScale);
			}


			void Value::DisplayInfo::SetAlpha(double a_alpha)
			{
				_alpha = a_alpha;
				SetFlags(Flag::kAlpha);
			}


			void Value::DisplayInfo::SetVisible(bool a_visible)
			{
				_visible = a_visible;
				SetFlags(Flag::kVisible);
			}


			void Value::DisplayInfo::SetZ(double a_z)
			{
				_z = a_z;
				SetFlags(Flag::kZ);
			}


			void Value::DisplayInfo::SetXRotation(double a_degrees)
			{
				_xRotation = a_degrees;
				SetFlags(Flag::kXRotation);
			}


			void Value::DisplayInfo::SetYRotation(double a_degrees)
			{
				_yRotation = a_degrees;
				SetFlags(Flag::kYRotation);
			}


			void Value::DisplayInfo::SetZScale(double a_zScale)
			{
				_zScale = a_zScale;
				SetFlags(Flag::kZScale);
			}


			void Value::DisplayInfo::SetFOV(double a_fov)
			{
				_fov = a_fov;
				SetFlags(Flag::kFOV);
			}


			void Value::DisplayInfo::SetProjectionMatrix3D(const Render::Matrix4F& a_matrix)
			{
				SetFlags(Flag::kProjMatrix3D);
				_projectionMatrix3D = a_matrix;
			}


			void Value::DisplayInfo::ClearProjectionMatrix3D()
			{
				ClearFlags(Flag::kProjMatrix3D);
			}


			void Value::DisplayInfo::SetViewMatrix3D(const Render::Matrix3F& a_matrix)
			{
				_viewMatrix3D = a_matrix;
				SetFlags(Flag::kViewMatrix3D);
			}


			void Value::DisplayInfo::ClearViewMatrix3D()
			{
				ClearFlags(Flag::kViewMatrix3D);
			}


			void Value::DisplayInfo::SetEdgeAAMode(Render::EdgeAAMode a_edgeAAMode)
			{
				_edgeAAMode = a_edgeAAMode;
				SetFlags(Flag::kEdgeAAMode);
			}


			void Value::DisplayInfo::SetPosition(double a_x, double a_y)
			{
				_x = a_x;
				_y = a_y;
				SetFlags(Flag::kX | Flag::kY);
			}


			void Value::DisplayInfo::SetScale(double a_xScale, double a_yScale)
			{
				_xScale = a_xScale;
				_yScale = a_yScale;
				SetFlags(Flag::kXScale | Flag::kYScale);
			}


			void Value::DisplayInfo::Set(double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible)
			{
				_x = a_x;
				_y = a_y;
				_rotation = a_rotation;
				_xScale = a_xScale;
				_yScale = a_yScale;
				_alpha = a_alpha;
				_visible = a_visible;
				SetFlags(Flag::kX | Flag::kY | Flag::kRotation | Flag::kXScale | Flag::kYScale | Flag::kAlpha | Flag::kVisible);
			}


			void Value::DisplayInfo::Set(double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible, double a_z, double a_xRotation, double a_yRotation, double a_zScale)
			{
				_x = a_x;
				_y = a_y;
				_rotation = a_rotation;
				_xScale = a_xScale;
				_yScale = a_yScale;
				_alpha = a_alpha;
				_visible = a_visible;
				_z = a_z;
				_xRotation = a_xRotation;
				_yRotation = a_yRotation;
				_zScale = a_zScale;
				SetFlags(Flag::kX | Flag::kY | Flag::kRotation | Flag::kXScale | Flag::kYScale | Flag::kAlpha | Flag::kVisible | Flag::kZ | Flag::kZScale | Flag::kXRotation | Flag::kYRotation);
			}


			double Value::DisplayInfo::GetX() const
			{
				assert(IsFlagSet(Flag::kX));
				return _x;
			}


			double Value::DisplayInfo::GetY() const
			{
				assert(IsFlagSet(Flag::kY));
				return _y;
			}


			double Value::DisplayInfo::GetRotation() const
			{
				assert(IsFlagSet(Flag::kRotation));
				return _rotation;
			}


			double Value::DisplayInfo::GetXScale() const
			{
				assert(IsFlagSet(Flag::kXScale));
				return _xScale;
			}


			double Value::DisplayInfo::GetYScale() const
			{
				assert(IsFlagSet(Flag::kYScale));
				return _yScale;
			}


			double Value::DisplayInfo::GetAlpha() const
			{
				assert(IsFlagSet(Flag::kAlpha));
				return _alpha;
			}


			bool Value::DisplayInfo::GetVisible() const
			{
				assert(IsFlagSet(Flag::kVisible));
				return _visible;
			}


			double Value::DisplayInfo::GetZ() const
			{
				assert(IsFlagSet(Flag::kZ));
				return _z;
			}


			double Value::DisplayInfo::GetXRotation() const
			{
				assert(IsFlagSet(Flag::kXRotation));
				return _xRotation;
			}


			double Value::DisplayInfo::GetYRotation() const
			{
				assert(IsFlagSet(Flag::kYRotation));
				return _yRotation;
			}


			double Value::DisplayInfo::GetZScale() const
			{
				assert(IsFlagSet(Flag::kZScale));
				return _zScale;
			}


			double Value::DisplayInfo::GetFOV() const
			{
				assert(IsFlagSet(Flag::kFOV));
				return _fov;
			}


			const Render::Matrix4F& Value::DisplayInfo::GetProjectionMatrix3D() const
			{
				assert(IsFlagSet(Flag::kProjMatrix3D));
				return _projectionMatrix3D;
			}


			const Render::Matrix3F& Value::DisplayInfo::GetViewMatrix3D() const
			{
				assert(IsFlagSet(Flag::kViewMatrix3D));
				return _viewMatrix3D;
			}


			Render::EdgeAAMode Value::DisplayInfo::GetEdgeAAMode() const
			{
				assert(IsFlagSet(Flag::kEdgeAAMode));
				return _edgeAAMode;
			}


			bool Value::DisplayInfo::IsFlagSet(Flag a_flag) const
			{
				return (_varsSet & a_flag) != Flag::kNone;
			}


			void Value::DisplayInfo::SetFlags(Flag a_flags)
			{
				_varsSet |= a_flags;
			}


			void Value::DisplayInfo::ClearFlags(Flag a_flags)
			{
				_varsSet &= ~a_flags;
			}


			bool Value::ObjectInterface::ObjVisitor::IncludeAS3PublicMembers() const
			{
				return false;
			}


			Value::ObjectInterface::ObjectInterface(MovieImpl* a_movieRoot) :
				_movieRoot(a_movieRoot)
			{}


			bool Value::ObjectInterface::IsSameContext(ObjectInterface* a_objInterface)
			{
				return (_movieRoot == a_objInterface->_movieRoot);
			}


			MovieImpl* Value::ObjectInterface::GetMovieImpl() const
			{
				return _movieRoot;
			}


			Value::Value() :
				_objectInterface(0),
				_type(ValueType::kUndefined),
				_pad0C(0),
				_value(),
				_dataAux(0)
			{}


			Value::Value(SInt32 a_val) :
				_objectInterface(0),
				_type(ValueType::kInt),
				_pad0C(0),
				_value(),
				_dataAux(0)
			{
				_value.signedInt = a_val;
			}


			Value::Value(UInt32 a_val) :
				_objectInterface(0),
				_type(ValueType::kUInt),
				_pad0C(0),
				_value(),
				_dataAux(0)
			{
				_value.unsignedInt = a_val;
			}


			Value::Value(double a_val) :
				_objectInterface(0),
				_type(ValueType::kNumber),
				_pad0C(0),
				_value(),
				_dataAux(0)
			{
				_value.number = a_val;
			}


			Value::Value(bool a_val) :
				_objectInterface(0),
				_type(ValueType::kBoolean),
				_pad0C(0),
				_value(),
				_dataAux(0)
			{
				_value.boolean = a_val;
			}


			Value::Value(const char* a_val) :
				_objectInterface(0),
				_type(ValueType::kString),
				_pad0C(0),
				_value(),
				_dataAux(0)
			{
				_value.string = a_val;
			}


			Value::Value(const wchar_t* a_val) :
				_objectInterface(0),
				_type(ValueType::kStringW),
				_pad0C(0),
				_value(),
				_dataAux(0)
			{
				_value.stringW = a_val;
			}


			Value::Value(const Value& a_val) :
				_objectInterface(0),
				_type(a_val._type),
				_pad0C(0),
				_value(a_val._value),
				_dataAux(a_val._dataAux)
			{
				if (a_val.IsManagedValue()) {
					AcquireManagedValue(a_val);
				}
			}


			Value::Value(Value&& a_val) :
				_objectInterface(std::move(a_val._objectInterface)),
				_type(std::move(a_val._type)),
				_pad0C(0),
				_value(std::move(a_val._value)),
				_dataAux(std::move(a_val._dataAux))
			{
				a_val._objectInterface = 0;
				a_val._type = ValueType::kUndefined;
				a_val._value.data = 0;
				a_val._dataAux = 0;
			}


			Value::~Value()
			{
				if (IsManagedValue()) {
					ReleaseManagedValue();
				}
				_type = ValueType::kUndefined;
			}


			Value& Value::operator=(const Value& a_rhs)
			{
				if (this == &a_rhs) {
					return *this;
				}

				if (IsManagedValue()) {
					ReleaseManagedValue();
				}

				_type = a_rhs._type;
				_value = a_rhs._value;
				_dataAux = a_rhs._dataAux;

				if (a_rhs.IsManagedValue()) {
					AcquireManagedValue(a_rhs);
				}

				return *this;
			}


			Value& Value::operator=(Value&& a_rhs)
			{
				if (this == &a_rhs) {
					return *this;
				}

				_objectInterface = std::move(a_rhs._objectInterface);
				a_rhs._objectInterface = 0;

				_type = std::move(a_rhs._type);
				a_rhs._type = ValueType::kUndefined;

				_value = std::move(a_rhs._value);
				a_rhs._value.data = 0;

				_dataAux = std::move(a_rhs._dataAux);
				a_rhs._dataAux = 0;

				return *this;
			}


			bool Value::operator==(const GFx::Value& a_rhs) const
			{
				auto type = GetType();
				if (type != a_rhs.GetType()) {
					return false;
				} else {
					switch (type) {
					case ValueType::kUndefined:
					case ValueType::kNull:
						return true;
					case ValueType::kBoolean:
						return _value.boolean == a_rhs._value.boolean;
					case ValueType::kInt:
						return _value.signedInt == a_rhs._value.signedInt;
					case ValueType::kUInt:
						return _value.unsignedInt == a_rhs._value.unsignedInt;
					case ValueType::kNumber:
						return _value.number == a_rhs._value.number;
					case ValueType::kString:
						return std::strcmp(GetString(), a_rhs.GetString()) == 0;
					case ValueType::kStringW:
						return std::wcscmp(GetStringW(), a_rhs.GetStringW()) == 0;
					case ValueType::kClosure:
						return (_value.data == a_rhs._value.data) && (_dataAux == a_rhs._dataAux);
					default:
						return _value.data == a_rhs._value.data;
					}
				}
			}


			auto Value::GetType() const
				-> ValueType
			{
				return _type & ValueType::kTypeMask;
			}


			bool Value::IsUndefined() const
			{
				return GetType() == ValueType::kUndefined;
			}


			bool Value::IsNull() const
			{
				return GetType() == ValueType::kNull;
			}


			bool Value::IsBool() const
			{
				return GetType() == ValueType::kBoolean;
			}


			bool Value::IsInt() const
			{
				return GetType() == ValueType::kInt;
			}


			bool Value::IsUInt() const
			{
				return GetType() == ValueType::kUInt;
			}


			bool Value::IsNumber() const
			{
				return GetType() == ValueType::kNumber;
			}


			bool Value::IsNumeric() const
			{
				switch (GetType()) {
				case ValueType::kInt:
				case ValueType::kUInt:
				case ValueType::kNumber:
					return true;
				default:
					return false;
				}
			}


			bool Value::IsString() const
			{
				return GetType() == ValueType::kString;
			}


			bool Value::IsStringW() const
			{
				return GetType() == ValueType::kStringW;
			}


			bool Value::IsObject() const
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


			bool Value::IsArray() const
			{
				return GetType() == ValueType::kArray;
			}


			bool Value::IsDisplayObject() const
			{
				return GetType() == ValueType::kDisplayObject;
			}


			bool Value::IsClosure() const
			{
				return GetType() == ValueType::kClosure;
			}


			bool Value::IsOrphaned() const
			{
				return (_type & ValueType::kOrphanedBit) != ValueType::kNone;
			}


			bool Value::GetBool() const
			{
				assert(IsBool());
				return _value.boolean;
			}


			SInt32 Value::GetInt() const
			{
				assert(IsInt());
				return _value.signedInt;
			}


			UInt32 Value::GetUInt() const
			{
				assert(IsUInt());
				return _value.unsignedInt;
			}


			double Value::GetNumber() const
			{
				assert(IsNumber());
				return _value.number;
			}


			const char* Value::GetString() const
			{
				assert(IsString());
				return IsManagedValue() ? *_value.stringManaged : _value.string;
			}


			const wchar_t* Value::GetStringW() const
			{
				assert(IsStringW());
				return _value.stringW;
			}


			void Value::SetUndefined()
			{
				ChangeType(ValueType::kUndefined);
			}


			void Value::SetNull()
			{
				ChangeType(ValueType::kNull);
			}


			void Value::SetBoolean(bool a_val)
			{
				ChangeType(ValueType::kBoolean);
				_value.boolean = a_val;
			}


			void Value::SetInt(SInt32 a_val)
			{
				ChangeType(ValueType::kInt);
				_value.signedInt = a_val;
			}


			void Value::SetUInt(UInt32 a_val)
			{
				ChangeType(ValueType::kUInt);
				_value.unsignedInt = a_val;
			}


			void Value::SetNumber(double a_val)
			{
				ChangeType(ValueType::kNumber);
				_value.number = a_val;
			}


			void Value::SetString(const char* a_val)
			{
				ChangeType(ValueType::kString);
				_value.string = a_val;
			}


			void Value::SetStringW(const wchar_t* a_val)
			{
				ChangeType(ValueType::kStringW);
				_value.stringW = a_val;
			}


			void Value::SetConvertBoolean()
			{
				ChangeType(ValueType::kConvertBoolean);
			}


			void Value::SetConvertNumber()
			{
				ChangeType(ValueType::kConvertNumber);
			}


			void Value::SetConvertString()
			{
				ChangeType(ValueType::kConvertString);
			}


			void Value::SetConvertStringW()
			{
				ChangeType(ValueType::kConvertStringW);
			}


			bool Value::HasMember(const char* a_name) const
			{
				assert(IsObject());
				return _objectInterface->HasMember(_value.data, a_name, IsDisplayObject());
			}


			bool Value::GetMember(const char* a_name, Value* a_val) const
			{
				assert(IsObject());
				return _objectInterface->GetMember(_value.data, a_name, a_val, IsDisplayObject());
			}


			bool Value::SetMember(const char* a_name, const Value& a_val)
			{
				assert(IsObject());
				return _objectInterface->SetMember(_value.data, a_name, a_val, IsDisplayObject());
			}


			bool Value::Invoke(const char* a_name, Value* a_result, const Value* a_args, UPInt a_numArgs)
			{
				assert(IsObject());
				return _objectInterface->Invoke(_value.data, a_result, a_name, a_args, a_numArgs, IsDisplayObject());
			}


			bool Value::Invoke(const char* a_name, Value* a_result)
			{
				return Invoke(a_name, a_result, 0, 0);
			}


			void Value::VisitMembers(ObjectVisitor* a_visitor) const
			{
				assert(IsObject());
				return _objectInterface->VisitMembers(_value.data, a_visitor, IsDisplayObject());
			}


			bool Value::DeleteMember(const char* a_name)
			{
				assert(IsObject());
				return _objectInterface->DeleteMember(_value.data, a_name, IsDisplayObject());
			}


			void Value::SetUserData(ASUserData* a_data)
			{
				assert(IsObject());
				_objectInterface->SetUserData(_value.data, a_data, IsDisplayObject());
			}


			ASUserData* Value::GetUserData() const
			{
				assert(IsObject());
				return _objectInterface->GetUserData(_value.data, IsDisplayObject());
			}


			bool Value::InvokeSelf(Value* a_result, const Value* a_args, UPInt a_numArgs)
			{
				assert(IsClosure());
				return _objectInterface->InvokeClosure(_value.data, _dataAux, a_result, a_args, a_numArgs);
			}


			bool Value::InvokeSelf(Value* a_result)
			{
				assert(IsClosure());
				return InvokeSelf(a_result, 0, 0);
			}


			UInt32 Value::GetArraySize() const
			{
				assert(IsArray());
				return _objectInterface->GetArraySize(_value.data);
			}


			bool Value::SetArraySize(UInt32 a_size)
			{
				assert(IsArray());
				return _objectInterface->SetArraySize(_value.data, a_size);
			}


			bool Value::GetElement(UInt32 a_idx, Value* a_val) const
			{
				assert(IsArray());
				return _objectInterface->GetElement(_value.data, a_idx, a_val);
			}


			bool Value::SetElement(UInt32 a_idx, const Value& a_val)
			{
				assert(IsArray());
				return _objectInterface->SetElement(_value.data, a_idx, a_val);
			}


			void Value::VisitElements(ArrayVisitor* a_visitor, UInt32 a_idx, SInt32 a_count) const
			{
				assert(IsArray());
				return _objectInterface->VisitElements(_value.data, a_visitor, a_idx, a_count);
			}


			void Value::VisitElements(ArrayVisitor* a_visitor) const
			{
				VisitElements(a_visitor, 0);
			}


			bool Value::PushBack(const Value& a_val)
			{
				assert(IsArray());
				return _objectInterface->PushBack(_value.data, a_val);
			}


			bool Value::PopBack(Value* a_val)
			{
				assert(IsArray());
				return _objectInterface->PopBack(_value.data, a_val);
			}


			bool Value::RemoveElements(UInt32 a_idx, SInt32 a_count)
			{
				assert(IsArray());
				return _objectInterface->RemoveElements(_value.data, a_idx, a_count);
			}


			bool Value::RemoveElement(UInt32 a_idx)
			{
				return RemoveElements(a_idx, 1);
			}


			bool Value::ClearElements()
			{
				return RemoveElements(0);
			}


			bool Value::IsByteArray() const
			{
				assert(IsObject());
				return _objectInterface->IsByteArray(_value.data);
			}


			UInt32 Value::GetByteArraySize() const
			{
				return _objectInterface->GetByteArraySize(_value.data);
			}


			bool Value::ReadFromByteArray(UInt8* a_destBuf, UPInt a_destBufSize)
			{
				return _objectInterface->ReadFromByteArray(_value.data, a_destBuf, a_destBufSize);
			}


			bool Value::WriteToByteArray(const UInt8* a_srcBuf, UPInt a_writeSize)
			{
				return _objectInterface->WriteToByteArray(_value.data, a_srcBuf, a_writeSize);
			}


			bool Value::IsDisplayObjectActive() const
			{
				assert(IsDisplayObject());
				return _objectInterface->IsDisplayObjectActive(_value.data);
			}


			bool Value::GetDisplayInfo(DisplayInfo* a_info) const
			{
				assert(IsDisplayObject());
				return _objectInterface->GetDisplayInfo(_value.data, a_info);
			}


			bool Value::SetDisplayInfo(const DisplayInfo& a_info)
			{
				assert(IsDisplayObject());
				return _objectInterface->SetDisplayInfo(_value.data, a_info);
			}


			bool Value::GetWorldMatrix(Render::Matrix2F* a_mat) const
			{
				assert(IsDisplayObject());
				return _objectInterface->GetWorldMatrix(_value.data, a_mat);
			}


			bool Value::GetDisplayMatrix(Render::Matrix2F* a_mat) const
			{
				assert(IsDisplayObject());
				return _objectInterface->GetDisplayMatrix(_value.data, a_mat);
			}


			bool Value::SetDisplayMatrix(const Render::Matrix2F& a_mat)
			{
				assert(IsDisplayObject());
				return _objectInterface->SetDisplayMatrix(_value.data, a_mat);
			}


			bool Value::GetMatrix3D(Render::Matrix3F* a_mat) const
			{
				assert(IsDisplayObject());
				return _objectInterface->GetMatrix3D(_value.data, a_mat);
			}


			bool Value::SetMatrix3D(const Render::Matrix3F& a_mat)
			{
				assert(IsDisplayObject());
				return _objectInterface->SetMatrix3D(_value.data, a_mat);
			}


			bool Value::GetColorTransform(Render::Cxform* a_cx) const
			{
				assert(IsDisplayObject());
				return _objectInterface->GetCxform(_value.data, a_cx);
			}


			bool Value::SetColorTransform(Render::Cxform& a_cx)
			{
				assert(IsDisplayObject());
				return _objectInterface->SetCxform(_value.data, a_cx);
			}


			bool Value::SetText(const char* a_text)
			{
				assert(IsDisplayObject());
				return _objectInterface->SetText(_value.data, a_text, false);
			}


			bool Value::SetText(const wchar_t* a_text)
			{
				assert(IsDisplayObject());
				return _objectInterface->SetText(_value.data, a_text, false);
			}


			bool Value::SetTextHTML(const char* a_html)
			{
				assert(IsDisplayObject());
				return _objectInterface->SetText(_value.data, a_html, true);
			}


			bool Value::SetTextHTML(const wchar_t* a_html)
			{
				assert(IsDisplayObject());
				return _objectInterface->SetText(_value.data, a_html, true);
			}


			bool Value::GetText(Value* a_val) const
			{
				assert(IsDisplayObject());
				return _objectInterface->GetText(_value.data, a_val, false);
			}


			bool Value::GetTextHTML(Value* a_val) const
			{
				assert(IsDisplayObject());
				return _objectInterface->GetText(_value.data, a_val, true);
			}


			bool Value::CreateEmptyMovieClip(GFx::Value* a_mc, const char* a_instanceName, SInt32 a_depth)
			{
				assert(IsDisplayObject());
				return _objectInterface->CreateEmptyMovieClip(_value.data, a_mc, a_instanceName, a_depth);
			}


			bool Value::AttachMovie(GFx::Value* a_mc, const char* a_symbolName, const char* a_instanceName, SInt32 a_depth, const MemberValueSet* a_initArgs)
			{
				assert(IsDisplayObject());
				return _objectInterface->AttachMovie(_value.data, a_mc, a_symbolName, a_instanceName, a_depth, a_initArgs);
			}


			bool Value::GotoAndPlay(const char* a_frame)
			{
				assert(IsDisplayObject());
				return _objectInterface->GotoAndPlay(_value.data, a_frame, false);
			}


			bool Value::GotoAndStop(const char* a_frame)
			{
				assert(IsDisplayObject());
				return _objectInterface->GotoAndPlay(_value.data, a_frame, true);
			}


			bool Value::GotoAndPlay(UInt32 a_frame)
			{
				assert(IsDisplayObject());
				return _objectInterface->GotoAndPlay(_value.data, a_frame, false);
			}


			bool Value::GotoAndStop(UInt32 a_frame)
			{
				assert(IsDisplayObject());
				return _objectInterface->GotoAndPlay(_value.data, a_frame, true);
			}


			Movie* Value::GetMovie() const
			{
				assert(IsObject());
				return reinterpret_cast<Movie*>(_objectInterface->GetMovieImpl());
			}


			Value::ValueUnion::ValueUnion() :
				data(0)
			{}


			bool Value::IsManagedValue() const
			{
				bool isManaged = ((_type & ValueType::kManagedBit) != ValueType::kNone);
				if (isManaged) {
					assert(_objectInterface != 0);
				}
				return isManaged;
			}


			void Value::ChangeType(ValueType a_type)
			{
				if (IsManagedValue()) {
					ReleaseManagedValue();
				}
				_value.data = 0;
				_type = a_type;
			}


			void Value::AcquireManagedValue(const Value& a_src)
			{
				assert(a_src._value.data && (a_src._objectInterface != 0));
				_objectInterface = a_src._objectInterface;
				_objectInterface->ObjectAddRef(this, _value.data);
			}


			void Value::ReleaseManagedValue()
			{
				assert(_value.data && (_objectInterface != 0));
				_objectInterface->ObjectRelease(this, _value.data);
				_objectInterface = 0;
			}
		}
	}
}
