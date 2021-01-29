#include "CageWall.h"
#include <DAF_Utility.h>

using namespace DAF::Geometry;
CageWall::CageWall(DirectX::XMFLOAT3 position)
{
	Prism verticalBar(4, 0.05f, 4.0f);
	Prism horizontalBar(4, 0.1f, 5.0f);
	horizontalBar.Rotate(0, 0, 90);

	auto barSize = verticalBar.Size();
	int vRepCount = 5.0 /  barSize.x / 2 - 1;
	int hRepCount = 4.0f / barSize.x / 2 - 1;

	verticalBar.Replicate(vRepCount, 2*barSize.x, { 1,0,0 });
	horizontalBar.Replicate(hRepCount, 2*barSize.x, { 0,1,0 });
	verticalBar.Center();
	horizontalBar.Center();

	Append(verticalBar);
	Append(horizontalBar);
		
	CalculateNormals();
	Translate(position);
}
