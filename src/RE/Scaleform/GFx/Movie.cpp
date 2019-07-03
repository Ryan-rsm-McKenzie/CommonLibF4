#include "RE/Scaleform/GFx/Movie.h"

#include "RE/Scaleform/GFx/ASMovieRootBase.h"
#include "RE/Scaleform/GFx/MovieDef.h"
#include "RE/Scaleform/GFx/Value.h"


namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			float Movie::GetRenderPixelScale()
			{
				return 20.0;
			}


			UInt32 Movie::GetFrameCount() const
			{
				return GetMovieDef()->GetFrameCount();
			}


			float Movie::GetFrameRate() const
			{
				return GetMovieDef()->GetFrameRate();
			}


			SInt32 Movie::GetAVMVersion() const
			{
				return _asMovieRoot->GetAVMVersion();
			}


			bool Movie::IsAvailable(const char* a_pathToVar) const
			{
				return _asMovieRoot->IsAvailable(a_pathToVar);
			}


			void Movie::CreateString(Value* a_value, const char* a_string)
			{
				_asMovieRoot->CreateString(a_value, a_string);
			}


			void Movie::CreateStringW(Value* a_value, const wchar_t* a_string)
			{
				_asMovieRoot->CreateStringW(a_value, a_string);
			}


			void Movie::CreateObject(Value* a_value, const char* a_className, const Value* a_args, UInt32 a_numArgs)
			{
				_asMovieRoot->CreateObject(a_value, a_className, a_args, a_numArgs);
			}


			void Movie::CreateArray(Value* a_value)
			{
				_asMovieRoot->CreateArray(a_value);
			}


			void Movie::CreateFunction(Value* a_value, FunctionHandler* a_fc, void* a_userData)
			{
				_asMovieRoot->CreateFunction(a_value, a_fc, a_userData);
			}


			bool Movie::SetVariable(const char* a_pathToVar, const Value& a_value, SetVarType a_setType)
			{
				return _asMovieRoot->SetVariable(a_pathToVar, a_value, a_setType);
			}


			bool Movie::GetVariable(Value* a_val, const char* a_pathToVar) const
			{
				return _asMovieRoot->GetVariable(a_val, a_pathToVar);
			}


			bool Movie::SetVariable(const char* a_pathToVar, const char* a_value, SetVarType a_setType)
			{
				Value value(a_value);
				return _asMovieRoot->SetVariable(a_pathToVar, value, a_setType);
			}


			bool Movie::SetVariable(const char* a_pathToVar, const wchar_t* a_value, SetVarType a_setType)
			{
				Value value(a_value);
				return _asMovieRoot->SetVariable(a_pathToVar, value, a_setType);
			}


			bool Movie::SetVariableDouble(const char* a_pathToVar, double a_value, SetVarType a_setType)
			{
				Value value(a_value);
				return _asMovieRoot->SetVariable(a_pathToVar, value, a_setType);
			}


			double Movie::GetVariableDouble(const char* a_pathToVar) const
			{
				Value value;
				return _asMovieRoot->GetVariable(&value, a_pathToVar) ? value.GetNumber() : 0.0;
			}


			bool Movie::SetVariableArray(SetArrayType a_type, const char* a_pathToVar, UInt32 a_index, const void* a_data, UInt32 a_count, SetVarType a_setType)
			{
				return _asMovieRoot->SetVariableArray(a_type, a_pathToVar, a_index, a_data, a_count, a_setType);
			}


			bool Movie::SetVariableArraySize(const char* a_pathToVar, UInt32 a_count, SetVarType a_setType)
			{
				return _asMovieRoot->SetVariableArraySize(a_pathToVar, a_count, a_setType);
			}


			UInt32 Movie::GetVariableArraySize(const char* a_pathToVar)
			{
				return _asMovieRoot->GetVariableArraySize(a_pathToVar);
			}


			bool Movie::GetVariableArray(SetArrayType a_type, const char* a_pathToVar, UInt32 a_index, void* a_data, UInt32 a_count)
			{
				return _asMovieRoot->GetVariableArray(a_type, a_pathToVar, a_index, a_data, a_count);
			}


			bool Movie::SetVariableArray(const char* a_pathToVar, UInt32 a_index, const Value* a_data, UInt32 a_count, SetVarType a_setType)
			{
				SetArrayType type;
				switch (a_data->GetType()) {
				case Value::ValueType::kInt:
					type = SetArrayType::kInt;
					break;
				case Value::ValueType::kNumber:
					type = SetArrayType::kDouble;
					break;
				case Value::ValueType::kString:
					type = SetArrayType::kString;
					break;
				case Value::ValueType::kStringW:
					type = SetArrayType::kStringW;
					break;
				default:
					type = SetArrayType::kValue;
					break;
				}

				return _asMovieRoot->SetVariableArray(type, a_pathToVar, a_index, a_data, a_count, a_setType);
			}


			bool Movie::GetVariableArray(const char* a_pathToVar, UInt32 a_index, Value* a_data, UInt32 a_count)
			{
				SetArrayType type;
				switch (a_data->GetType()) {
				case Value::ValueType::kInt:
					type = SetArrayType::kInt;
					break;
				case Value::ValueType::kNumber:
					type = SetArrayType::kDouble;
					break;
				case Value::ValueType::kString:
					type = SetArrayType::kString;
					break;
				case Value::ValueType::kStringW:
					type = SetArrayType::kStringW;
					break;
				default:
					type = SetArrayType::kValue;
					break;
				}

				return _asMovieRoot->GetVariableArray(type, a_pathToVar, a_index, a_data, a_count);
			}


			bool Movie::Invoke(const char* a_pathToMethod, Value* a_result, const Value* a_args, UInt32 a_numArgs)
			{
				return _asMovieRoot->Invoke(a_pathToMethod, a_result, a_args, a_numArgs);
			}


			bool Movie::Invoke(const char* a_pathToMethod, Value* a_result, const char* a_argFmt, ...)
			{
				std::va_list args;
				va_start(args, a_argFmt);
				auto result = _asMovieRoot->Invoke(a_pathToMethod, a_result, a_argFmt, args);
				va_end(args);
				return result;
			}


			bool Movie::InvokeArgs(const char* a_pathToMethod, Value* a_result, const char* a_argFmt, std::va_list a_args)
			{
				return _asMovieRoot->Invoke(a_pathToMethod, a_result, a_argFmt, a_args);
			}


			bool Movie::Invoke(const char* a_pathToMethod, const char* a_argFmt, ...)
			{
				std::va_list args;
				va_start(args, a_argFmt);
				Value result;
				auto success = _asMovieRoot->Invoke(a_pathToMethod, &result, a_argFmt, args);
				va_end(args);
				return success;
			}


			void Movie::SetExternalInterfaceRetVal(const Value& a_val)
			{
				_asMovieRoot->SetExternalInterfaceRetVal(a_val);
			}


			void Movie::Release()
			{
				_asMovieRoot.reset();
			}
		}
	}
}
