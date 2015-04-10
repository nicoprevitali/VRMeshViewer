#include "renderer/PerspectiveRenderer.hpp"

VR_NAMESPACE_BEGIN

PerspectiveRenderer::PerspectiveRenderer (std::shared_ptr<GLShader> &shader, float fov, float aspectRatio, float zNear, float zFar)
	: Renderer(shader), fov(fov), aspectRatio(aspectRatio), zNear(zNear), zFar(zFar), fH(tan(fov / 360 * M_PI ) * zNear), fW(fH * aspectRatio) {

	projectionMatrix = frustum(-fW, fW, -fH, fH, zNear, zFar);

	viewMatrix = lookAt(
		Vector3f(4, 3, -3), // Camera is at (4,3,-3), in world space
		Vector3f(0, 0, 0), // And looks at the origin
		Vector3f(0, 1, 0) // Head is up
	);

	modelMatrix = Matrix4f::Identity();

	mvp = projectionMatrix * viewMatrix * modelMatrix;
}

void PerspectiveRenderer::preProcess () {
	Renderer::preProcess();
	shader->bind();
	shader->uploadIndices(mesh->getIndices());
	shader->uploadAttrib("position", mesh->getVertices());
	shader->setUniform("intensity", 0.3f);
}

void PerspectiveRenderer::update () {
	shader->bind();
	shader->setUniform("mvp", mvp);
}

void PerspectiveRenderer::draw() {
	shader->bind();
	shader->drawIndexed(GL_TRIANGLES, 0, mesh->getNumFaces());
}

void PerspectiveRenderer::cleanUp () {

}

VR_NAMESPACE_END