include $(CLEAR_VARS)
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/Box2D/ \
	$(LOCAL_PATH)./

BOX2D_PATH := Box2D/

#$(LOCAL_PATH)/../Box2D/ \

LOCAL_CFLAGS := \
								-g3 \
								-ggdb \
								-gstabs+ \
								-DANDROID_NDK \

TARGET_ABI			:= android-4-armeabi
LOCAL_MODULE		:= libBox2D
LOCAL_SRC_FILES 	:= \
	$(BOX2D_PATH)/Collision/b2BroadPhase.cpp \
	$(BOX2D_PATH)/Collision/b2CollideCircle.cpp \
	$(BOX2D_PATH)/Collision/b2CollidePolygon.cpp \
	$(BOX2D_PATH)/Collision/b2Collision.cpp \
	$(BOX2D_PATH)/Collision/b2Distance.cpp \
	$(BOX2D_PATH)/Collision/b2DynamicTree.cpp \
	$(BOX2D_PATH)/Collision/b2TimeOfImpact.cpp \
	$(BOX2D_PATH)/Collision/Shapes/b2CircleShape.cpp \
	$(BOX2D_PATH)/Collision/Shapes/b2PolygonShape.cpp \
	$(BOX2D_PATH)/Common/b2BlockAllocator.cpp \
	$(BOX2D_PATH)/Common/b2Math.cpp \
	$(BOX2D_PATH)/Common/b2Settings.cpp \
	$(BOX2D_PATH)/Common/b2StackAllocator.cpp \
	$(BOX2D_PATH)/Dynamics/b2Body.cpp \
	$(BOX2D_PATH)/Dynamics/b2ContactManager.cpp \
	$(BOX2D_PATH)/Dynamics/b2Fixture.cpp \
	$(BOX2D_PATH)/Dynamics/b2Island.cpp \
	$(BOX2D_PATH)/Dynamics/b2World.cpp \
	$(BOX2D_PATH)/Dynamics/b2WorldCallbacks.cpp \
	$(BOX2D_PATH)/Dynamics/Contacts/b2CircleContact.cpp \
	$(BOX2D_PATH)/Dynamics/Contacts/b2Contact.cpp \
	$(BOX2D_PATH)/Dynamics/Contacts/b2ContactSolver.cpp \
	$(BOX2D_PATH)/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
	$(BOX2D_PATH)/Dynamics/Contacts/b2PolygonContact.cpp \
	$(BOX2D_PATH)/Dynamics/Contacts/b2TOISolver.cpp \
	$(BOX2D_PATH)/Dynamics/Joints/b2DistanceJoint.cpp \
	$(BOX2D_PATH)/Dynamics/Joints/b2FrictionJoint.cpp \
	$(BOX2D_PATH)/Dynamics/Joints/b2GearJoint.cpp \
	$(BOX2D_PATH)/Dynamics/Joints/b2Joint.cpp \
	$(BOX2D_PATH)/Dynamics/Joints/b2LineJoint.cpp \
	$(BOX2D_PATH)/Dynamics/Joints/b2MouseJoint.cpp \
	$(BOX2D_PATH)/Dynamics/Joints/b2PrismaticJoint.cpp \
	$(BOX2D_PATH)/Dynamics/Joints/b2PulleyJoint.cpp \
	$(BOX2D_PATH)/Dynamics/Joints/b2RevoluteJoint.cpp \
	$(BOX2D_PATH)/Dynamics/Joints/b2WeldJoint.cpp \

include $(BUILD_STATIC_LIBRARY)


