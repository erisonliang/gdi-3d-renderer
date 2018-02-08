#include "Polygon.h"
#include "Matrix.h"

namespace GL {

	Polygon::Polygon(const Vector3 &first, const Vector3 &second, const Vector3 &third) 
		: Polygon(Vector4(first), Vector4(second), Vector4(third)) { }

	Polygon::Polygon(const Vector4 &first, const Vector4 &second, const Vector4 &third) {
		vertices = std::vector<Vector4>{ first, second, third };
		// colors are initially all zero (black/transparent)
		colors = std::vector<Vector4> { Vector4(), Vector4(), Vector4() };
		calculateNormals();
	}

	void Polygon::setColor(const Vector4 & col) {
		colors = std::vector<Vector4> { col, col, col };
	}

	void Polygon::setColors(const Vector4 &first, const Vector4 &second, const Vector4 &third) {
		colors = std::vector<Vector4> { first, second, third };
	}

	void Polygon::setColors(const Vector3 &first, const Vector3 &second, const Vector3 &third) {
		colors = std::vector<Vector4> { Vector4(first), Vector4(second), Vector4(third) };
	}

	void Polygon::setNormals(const Vector4 &first, const Vector4 &second, const Vector4 &third) {
		normals = std::vector<Vector3> { first.toVec3(), second.toVec3(), third.toVec3() };
	}

	void Polygon::setNormals(const Vector3 &first, const Vector3 &second, const Vector3 &third) {
		normals = std::vector<Vector3> { first, second, third };
	}

	void Polygon::calculateNormals() {
		Vector3 normal = Util::normal(vertices[0].fromHomogeneous(), vertices[1].fromHomogeneous(), vertices[2].fromHomogeneous());
		normals = std::vector<Vector3> { normal, normal, normal };
	}

	Polygon Polygon::getTransformed(const Matrix4 &mat) {
		Polygon transformed(vertices[0], vertices[1], vertices[2]);
		for (int i = 0; i < vertices.size(); i++) {
			transformed.vertices[i] = mat * vertices[i];
			transformed.colors[i] = colors[i];
			// TODO: transform normals
		}
		return transformed;
	}
}