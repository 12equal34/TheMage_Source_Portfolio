#pragma once

#define UE_DEBUG_SCREENMESSAGE(MessageString) \
	if (GEngine) \
	{\
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.f, FColor::Magenta, (MessageString));\
	}

#define UE_DEBUG_SCREENMESSAGE_FMT(FmtStr, ...) \
	if (GEngine) \
	{\
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.f, FColor::Magenta, FString::Printf((FmtStr), __VA_ARGS__));\
	}