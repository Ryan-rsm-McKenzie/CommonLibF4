#pragma once


namespace RE
{
	namespace Scaleform
	{
		namespace Render
		{
			template <class T>
			class Matrix4x4Data
			{
			public:
				Matrix4x4Data() :
					data{}
				{}


				// members
				T data[4][4];	// 00
			};


			template<>
			class Matrix4x4Data<float>
			{
			public:
				Matrix4x4Data() :
					data{ 0.0 }
				{}


				alignas(0x10) float data[4][4];	// 00
			};
			STATIC_ASSERT(sizeof(Matrix4x4Data<float>) == 0x40);
		}
	}
}
