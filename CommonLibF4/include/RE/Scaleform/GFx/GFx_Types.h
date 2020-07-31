#pragma once

#include "RE/Scaleform/Render/Render_Color.h"
#include "RE/Scaleform/Render/Render_Matrix2x4.h"
#include "RE/Scaleform/Render/Render_Matrix3x4.h"
#include "RE/Scaleform/Render/Render_Matrix4x4.h"
#include "RE/Scaleform/Render/Render_Types2D.h"

namespace RE
{
	namespace Scaleform
	{
		namespace GFx
		{
			using Render::Color;
			using Render::Matrix2F;
			using Render::Matrix3F;
			using Render::Matrix4F;
			using Render::Point;
			using Render::PointF;
			using Render::Rect;
			using Render::RectF;

			enum class PlayState
			{
				kPlaying,
				kStopped
			};
		}
	}
}