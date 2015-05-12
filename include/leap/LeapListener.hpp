#pragma once

#include "common.hpp"
#include "mesh/Mesh.hpp"
#include "Leap.h"
#include "leap/SkeletonHand.hpp"

VR_NAMESPACE_BEGIN

/**
 * @brief Leap listener
 *
 * Implements the leap API
 */
class LeapListener : public Leap::Listener {
public:
	LeapListener(bool useRift);
	virtual ~LeapListener () = default;

	/**
	 * Leap listener implementation
	 */
	virtual void onInit(const Leap::Controller &controller) {}
	virtual void onConnect (const Leap::Controller &controller);
	virtual void onDisconnect (const Leap::Controller &controller);
	virtual void onExit(const Leap::Controller &controller) {}
	virtual void onFrame (const Leap::Controller &controller);

	virtual void onServiceConnect (const Leap::Controller &controller);
	virtual void onServiceDisconnect (const Leap::Controller &controller);

	/**
	 * @brief Updates the window and framebuffer sizes
	 */
	void setSize (float windowWidth, float windowHeight, float FBWidth, float FBHeight) {
		this->windowHeight = windowWidth; this->windowHeight = windowHeight;
		this->FBWidth = FBWidth; this->FBHeight = FBHeight;
	}

	/**
	 * @brief Set the leap hands
	 */
	void setHands (std::shared_ptr<SkeletonHand> &l, std::shared_ptr<SkeletonHand> &r) {
		leftHand = l; rightHand = r;
	}

	/**
	* @brief Sets the pointer to the Hmd
	*/
	void setHmd(ovrHmd h) {
		hmd = h;
	}

protected:

	/**
	 * @brief Transforms a Leap vector into a Leap world vector
	 *
	 * @param v Leap vector
	 */
	Leap::Vector leapToWorld (Leap::Vector &v);

	/**
	* @brief Returns the transformation matrix from Leap to World coordinates
	*/
	Matrix4f getTransformationMatrix();

	/**
	 * @brief Leap to Eigen conversion
	 */
	Vector3f leapToEigen (Leap::Vector v) {
		return Vector3f(v.x, v.y, v.z);
	}

protected:

	bool riftMounted; ///< Leap on HMD?
	std::string fingerNames[5]; ///< Finger names
	std::string boneNames[4]; ///< Bone names
	std::string stateNames[4]; ///< Leap states
	float windowWidth, windowHeight; ///y GLFW window size
	float FBWidth, FBHeight; ///< Framebuffer size
	std::shared_ptr<SkeletonHand> leftHand, rightHand, currentHand; ///< Leap hands
	ovrHmd hmd; ///< The Rift
};

VR_NAMESPACE_END
