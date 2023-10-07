// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerSessionsSubsystem.generated.h"
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