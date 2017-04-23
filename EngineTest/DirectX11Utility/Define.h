#pragma once

#define D3D_SAFE_RELEASE( x ) if( x ) { x->Release(); x = nullptr; }