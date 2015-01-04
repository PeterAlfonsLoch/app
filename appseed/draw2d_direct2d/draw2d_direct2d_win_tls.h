#pragma once


// Windows Desktop Thread Local Storage for Draw2d Direct2d plugin


interface IDWriteFactory;
interface ID2D1Factory1;
interface ID3D11Device;
interface ID3D11DeviceContext;
interface ID3D11Device1;
interface IDXGIDevice;

CLASS_DECL_DRAW2D_DIRECT2D IDWriteFactory * TlsGetWriteFactory(bool bCreate = true);
CLASS_DECL_DRAW2D_DIRECT2D ID2D1Factory1 * GetD2D1Factory1(bool bCreate = true);
CLASS_DECL_DRAW2D_DIRECT2D ID3D11Device * TlsGetD3D11Device();
CLASS_DECL_DRAW2D_DIRECT2D ID3D11DeviceContext * TlsGetD3D11DeviceContext();
CLASS_DECL_DRAW2D_DIRECT2D ID3D11DeviceContext1 * TlsGetD3D11DeviceContext1();
CLASS_DECL_DRAW2D_DIRECT2D ID3D11Device1 * TlsGetD3D11Device1();
CLASS_DECL_DRAW2D_DIRECT2D IDXGIDevice * TlsGetDXGIDevice();
CLASS_DECL_DRAW2D_DIRECT2D ID2D1Device * TlsGetD2D1Device();
CLASS_DECL_DRAW2D_DIRECT2D ID2D1DeviceContext * TlsGetD2D1DeviceContext();

#define TLS_WRITE_FACTORY     248
#define TLS_D2D1_FACTORY1     13
#define TLS_d3_1              14
#define TLS_d3_2              15
#define TLS_d3_3              16
#define TLS_d3_4              17
#define TLS_MESSAGE_QUEUE     127


CLASS_DECL_DRAW2D_DIRECT2D float point_dpi(float points);
CLASS_DECL_DRAW2D_DIRECT2D float dpiy(float y);
CLASS_DECL_DRAW2D_DIRECT2D float dpix(float y);
CLASS_DECL_DRAW2D_DIRECT2D float y_dpi(float y);
CLASS_DECL_DRAW2D_DIRECT2D float x_dpi(float y);

