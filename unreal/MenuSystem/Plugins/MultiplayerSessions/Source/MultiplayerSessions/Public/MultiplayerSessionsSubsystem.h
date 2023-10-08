// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "MultiplayerSessionsSubsystem.generated.h"
// �Զ���ί��
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful);
/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSessionsSubsystem();

	//to handle session functionality 
	void CreateSession(int32 NumPublicConnections,FString MatchType); // ����session

	void FindSessions(int32 MaxSearchResults); // ����sessions

	void JoinSession(const FOnlineSessionSearchResult& SessionResult); // ����session

	void DestorySession();// ����session

	void StartSession(); // ����session

	// �Զ����MultiplayerOnCreateSessionComplete ����
	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;


protected:

	// internal callbacks  for the delegate 
	// ����Ҫ����������лص�
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	void OnFindSessionsComplete(bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName,EOnJoinSessionCompleteResult::Type Result);

	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	void OnStartSessionComplete(FName SessionName,bool bWasSuccessful);

private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;

	// to add to the online session interface delagate list
	// will bind MultiplayerSessionsSubsystem internal callbacks to these
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;

	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;

	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;
};