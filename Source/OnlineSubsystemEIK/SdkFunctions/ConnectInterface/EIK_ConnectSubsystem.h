﻿// Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemEIK/SdkFunctions/EIK_SharedFunctionFile.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EIK_ConnectSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEIK, Log, All);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAuthExpirationCallback, FEIK_ProductUserId, LocalUserId);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLoginStatusChangedCallback, FEIK_ProductUserId, LocalUserId, TEnumAsByte<EIK_ELoginStatus>, LoginStatus);

UCLASS()
class ONLINESUBSYSTEMEIK_API UEIK_ConnectSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	FOnAuthExpirationCallback OnAuthExpiration;
	FOnLoginStatusChangedCallback OnLoginStatusChanged;

	//Register to receive upcoming authentication expiration notifications. Notification is approximately 10 minutes prior to expiration. Call EOS_Connect_Login again with valid third party credentials to refresh access.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Connect Interface", DisplayName="EOS_Connect_AddNotifyAuthExpiration")
	FEIK_NotificationId EIK_Connect_AddNotifyAuthExpiration(const FOnAuthExpirationCallback& Callback);

	//Register to receive user login status updates.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Connect Interface", DisplayName="EOS_Connect_AddNotifyLoginStatusChanged")
	FEIK_NotificationId EIK_Connect_AddNotifyLoginStatusChanged(const FOnLoginStatusChangedCallback& Callback);

	//Fetches an ID token for a Product User ID.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Connect Interface", DisplayName="EOS_Connect_CopyIdToken")
	TEnumAsByte<EEIK_Result> EIK_Connect_CopyIdToken(FEIK_ProductUserId LocalUserId, FEIK_Connect_IdToken& OutIdToken);

	//Fetch information about an external account linked to a Product User ID. On a successful call, the caller must release the returned structure using the EOS_Connect_ExternalAccountInfo_Release API.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Connect Interface", DisplayName="EOS_Connect_CopyProductUserExternalAccountByAccountId")
	TEnumAsByte<EEIK_Result> EIK_Connect_CopyProductUserExternalAccountByAccountId(FEIK_ProductUserId LocalUserId, FString AccountId, FEIK_Connect_ExternalAccountInfo& OutExternalAccountInfo);

	//Fetch information about an external account of a specific type linked to a Product User ID. On a successful call, the caller must release the returned structure using the EOS_Connect_ExternalAccountInfo_Release API.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Connect Interface", DisplayName="EOS_Connect_CopyProductUserExternalAccountByAccountType")
	TEnumAsByte<EEIK_Result> EIK_Connect_CopyProductUserExternalAccountByAccountType(FEIK_ProductUserId LocalUserId, TEnumAsByte<EEIK_EExternalAccountType> AccountType, FEIK_Connect_ExternalAccountInfo& OutExternalAccountInfo);

	//Fetch information about an external account linked to a Product User ID. On a successful call, the caller must release the returned structure using the EOS_Connect_ExternalAccountInfo_Release API.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Connect Interface", DisplayName="EOS_Connect_CopyProductUserExternalAccountByIndex")
	TEnumAsByte<EEIK_Result> EIK_Connect_CopyProductUserExternalAccountByIndex(FEIK_ProductUserId LocalUserId, int32 Index, FEIK_Connect_ExternalAccountInfo& OutExternalAccountInfo);

	//Fetch information about a Product User, using the external account that they most recently logged in with as the reference. On a successful call, the caller must release the returned structure using the EOS_Connect_ExternalAccountInfo_Release API.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Connect Interface", DisplayName="EOS_Connect_CopyProductUserInfo")
	TEnumAsByte<EEIK_Result> EIK_Connect_CopyProductUserInfo(FEIK_ProductUserId LocalUserId, FEIK_Connect_ExternalAccountInfo& OutProductUserInfo);

	//Release the memory associated with an external account info. This must be called on data retrieved from EOS_Connect_CopyProductUserExternalAccountByIndex, EOS_Connect_CopyProductUserExternalAccountByAccountType, EOS_Connect_CopyProductUserExternalAccountByAccountId or EOS_Connect_CopyProductUserInfo.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Connect Interface", DisplayName="EOS_Connect_ExternalAccountInfo_Release")
	void EIK_Connect_ExternalAccountInfo_Release(FEIK_Connect_ExternalAccountInfo ExternalAccountInfo);

	//Fetch a Product User ID that maps to an external account ID cached from a previous query.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Connect Interface", DisplayName="EOS_Connect_GetExternalAccountMapping")
	FEIK_ProductUserId EIK_Connect_GetExternalAccountMapping(FEIK_ProductUserId LocalUserId, EEIK_EExternalAccountType AccountIdType, FString TargetExternalUserId);

	//Fetch a Product User ID that is logged in. This Product User ID is in the Epic Online Services namespace.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Connect Interface", DisplayName="EOS_Connect_GetLoggedInUserByIndex")
	FEIK_ProductUserId EIK_Connect_GetLoggedInUserByIndex(int32 Index);
};
