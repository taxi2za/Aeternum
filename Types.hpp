#pragma once

//# DO NOT C&P IF U DUNNO HOW TO USE IT
//> he4rtbleed - https://github.com/he4rtbleed/Aeternum

#define M_PI		3.14159265358979323846
#define M_PI_F		((float)(M_PI))
#define DEG2RAD(x)  ( (float)(x) * (float)(M_PI_F / 180.f) )
#define RAD2DEG(x)  ( (float)(x) * (float)(180.f / M_PI_F) )

namespace Aeternum
{
#pragma pack(push, 1)
	class Vector2
	{
	public:
		float x;
		float y;

		inline Vector2() : x(0), y(0){}

		inline Vector2(float X, float Y) : x(X), y(Y) { }

		__forceinline Vector2 operator-(const Vector2& V) {
			return Vector2(x - V.x, y - V.y);
		}

		__forceinline Vector2 operator+(const Vector2& V) {
			return Vector2(x + V.x, y + V.y);
		}

		__forceinline Vector2 operator*(float Scale) const {
			return Vector2(x * Scale, y * Scale);
		}

		__forceinline Vector2 operator/(float Scale) const {
			const float RScale = 1.f / Scale;
			return Vector2(x * RScale, y * RScale);
		}

		__forceinline float Size() const {
			return sqrt(x * x + y * y);
		}

		__forceinline float DistTo(Vector2 targetTo) const {
			return (targetTo - *this).Size();
		}
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct Vector3
	{
	public:
		float x;
		float y;
		float z;

		inline Vector3()
			: x(0), y(0), z(0) {
		}

		inline Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		__forceinline Vector3 operator-(const Vector3& V) {
			return Vector3(x - V.x, y - V.y, z - V.z);
		}

		__forceinline Vector3 operator+(const Vector3& V) {
			return Vector3(x + V.x, y + V.y, z + V.z);
		}

		__forceinline Vector3 operator*(float Scale) const {
			return Vector3(x * Scale, y * Scale, z * Scale);
		}

		__forceinline Vector3 operator/(float Scale) const {
			const float RScale = 1.f / Scale;
			return Vector3(x * RScale, y * RScale, z * RScale);
		}

		__forceinline Vector3 operator+(float A) const {
			return Vector3(x + A, y + A, z + A);
		}

		__forceinline Vector3 operator-(float A) const {
			return Vector3(x - A, y - A, z - A);
		}

		__forceinline Vector3 operator*(const Vector3& V) const {
			return Vector3(x * V.x, y * V.y, z * V.z);
		}

		__forceinline Vector3 operator/(const Vector3& V) const {
			return Vector3(x / V.x, y / V.y, z / V.z);
		}

		__forceinline float operator|(const Vector3& V) const {
			return x * V.x + y * V.y + z * V.z;
		}

		__forceinline float operator^(const Vector3& V) const {
			return x * V.y - y * V.x - z * V.z;
		}

		__forceinline Vector3& operator+=(const Vector3& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		__forceinline Vector3& operator-=(const Vector3& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		__forceinline Vector3& operator*=(const Vector3& v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}

		__forceinline Vector3& operator/=(const Vector3& v) {
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}

		__forceinline bool operator==(const Vector3& src) const {
			return (src.x == x) && (src.y == y) && (src.z == z);
		}

		__forceinline bool operator!=(const Vector3& src) const {
			return (src.x != x) || (src.y != y) || (src.z != z);
		}

		__forceinline Vector3 Rotate(float angle)
		{
			return Vector3( x * cos(-angle) - z * sin(-angle), y, x * sin(-angle) + z * cos(-angle));
		}

		__forceinline float Size() const {
			return sqrt(x * x + y * y + z * z);
		}

		__forceinline float DistTo(Vector3 targetTo) const {
			return (targetTo - *this).Size();
		}

		__forceinline Vector3 toRotator(Vector3 targetTo)
		{
			Vector3 Normalized = (targetTo - *this);
			return Normalized * (1 / Normalized.Size());
		}
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct Color
	{
		std::uint8_t R{ 255 };
		std::uint8_t G{ 255 };
		std::uint8_t B{ 255 };
		std::uint8_t A{ 255 };

		DWORD ApplyAlpha(uint8_t Alpha)
		{
			return ((Alpha & 0xff) << 24) | ((R & 0xff)) | ((G & 0xff) << 8) | ((B & 0xff) << 16);
		}

		DWORD RGBA2ARGB(uint8_t Alpha)
		{
			return ((Alpha & 0xff) << 24) | ((B & 0xff)) | ((G & 0xff) << 8) | ((R & 0xff) << 16);
		}
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct Matrix {
		float m11, m12, m13, m14,
			m21, m22, m23, m24,
			m31, m32, m33, m34,
			m41, m42, m43, m44;

		XMFLOAT3 GetCameraVec()
		{
			float	A = m22 * m33 - m32 * m23,
					B = m32 * m13 - m12 * m33,
					C = m12 * m23 - m22 * m13,
					Z = m11 * A + m21 * B + m31 * C;

			if (abs(Z) < 0.0001) return XMFLOAT3();

			float	D = m31 * m23 - m21 * m33,
					E = m11 * m33 - m31 * m13,
					F = m21 * m13 - m11 * m23,
					G = m21 * m32 - m31 * m22,
					H = m31 * m12 - m11 * m32,
					K = m11 * m22 - m21 * m12;

			return XMFLOAT3(-(A * m41 + D * m42 + G * m43) / Z, -(B * m41 + E * m42 + H * m43) / Z, -(C * m41 + F * m42 + K * m43) / Z);
		}

		bool WorldToScreen(XMFLOAT3 worldPos, XMFLOAT2 *OutPos) {
			float screenX = (m11 * worldPos.x) + (m21 * worldPos.y) + (m31 * worldPos.z) + m41;
			float screenY = (m12 * worldPos.x) + (m22 * worldPos.y) + (m32 * worldPos.z) + m42;
			float screenW = (m14 * worldPos.x) + (m24 * worldPos.y) + (m34 * worldPos.z) + m44;

			float camX = g_Width / 2.0f;
			float camY = g_Height / 2.0f;

			float x = camX + (camX * screenX / screenW);
			float y = camY - (camY * screenY / screenW);

			OutPos->x = x;
			OutPos->y = y;

			return (screenW > 0.001f);
		}
	};
#pragma pack(pop)
}
