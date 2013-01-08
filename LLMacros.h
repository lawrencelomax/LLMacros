//
//  LLMacros.h
//
//  Created by Lawrence Lomax on 17/09/2012.
//  Copyright (c) 2012 Lawrence Lomax. All rights reserved.
//

// Thread Safe shared instance singleton macro
#define DEFINE_SHARED_INSTANCE_USING_BLOCK(block) \
{\
static dispatch_once_t pred = 0; \
__strong static id _sharedObject = nil; \
dispatch_once(&pred, ^{ \
_sharedObject = block(); \
}); \
return _sharedObject; \
}

// Shared Instance declaration
#define SHARED_INSTANCE_HEADER(class) + (class) sharedInstance;
#define SHARED_INSTANCE_IMPLEMENTATION(class, sharedObjectBlock) \
+ (class) sharedInstance \
{ \
DEFINE_SHARED_INSTANCE_USING_BLOCK(sharedObjectBlock) \
}


// Weakself macro for use in blocks
#if __has_feature(objc_arc_weak)
#define LL_WEAK_TYPE(object) __weak __typeof__(object)
#define LL_WEAK_DECL(object, name) LL_WEAK_TYPE(object) name = object;
#define LL_WEAK_DECL_SUFFIX(object, suffix) LL_WEAK_DECL(object, suffix##_##object)
#define LL_WEAK(object) LL_WEAK_DECL_SUFFIX(object, weak)
#define LL_WEAKSELF LL_WEAK_DECL(self, weakSelf)
#else
#define LL_WEAK_TYPE(object) __block __typeof__(object)
#define LL_WEAK_DECL(object, name) LL_WEAK_TYPE(object) name = object;
#define LL_WEAK_DECL_SUFFIX(object, suffix) LL_WEAK_DECL(object, suffix##_##object)
#define LL_WEAK(object) LL_WEAK_DECL_SUFFIX(object, weak)
#define LL_WEAKSELF LL_WEAK_DECL(self, weakSelf)
#endif

// Helpers For Bitwise Enums
#define LLBitmaskOn(enum, mask) ( (enum & mask) == mask )
#define LLBitmaskOff(enum, mask) ( (enum & mask) != mask )

// Some Helpers for returning
#define LLIsNull(value) (value == nil || value == NULL || [value isEqual:[NSNull null]])

#define LLNotNull(value) (!(LLIsNull(value)))

#define LLReturnIfTrue(errorRef, errorString, condition) \
if((condition)) \
{ \
LLReturnWithErrorString(errorRef,errorString) \
}


#define LLBlockCallSafe(block, blockCall) \
{ \
    if(LLNotNull(block)) \
    { \
        blockCall; \
    } \
}

// Helpers for Debug logging
#ifdef DEBUG
#define LLDebugLog(...) NSLog(__VA_ARGS__)
#define LLDebugLogInfo(fmt, ...) NSLog((@"%s %s [Line %d] " fmt), __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define LLDebugLog(...) {}
#define LLDebugLogInfo(fmt, ...) {}
#endif

// Return early
#define BAIL_IF_TRUE(condition, bail) if(condition){ return bail; }
#define BAIL_IF_FALSE(condition, bail) if(!(condition)){ return bail; }

// Destroy macro
#define SAFE_RELEASE(object) {[object release]; object = nil;}