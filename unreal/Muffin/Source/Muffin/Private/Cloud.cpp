

// Fill out your copyright notice in the Description page of Project Settings.


#include "Cloud.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstance.h"
#include "MuffinCharacter.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"


// Sets default values
ACloud::ACloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	SetRootComponent(BoxCollision);

	CloudPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CloudPlane"));
	CloudPlane->SetupAttachment(RootComponent);

	RainPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RainPlane"));
	RainPlane->SetupAttachment(CloudPlane);

	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText"));
	ScoreText->SetupAttachment(RootComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(CloudPlane);
}

// Called when the game starts or when spawned
void ACloud::BeginPlay()
{
	Super::BeginPlay();
	SetRandomCloudTexture();
	EnableRain();
	
}

void ACloud::SetRandomCloudTexture()
{
	MatInterface = CloudPlane->GetMaterial(0); // ��ȡ����ĵ�һ�� ����
	MatInstance = CloudPlane->CreateDynamicMaterialInstance(0, MatInterface); // ���ݲ������� instance
	int Index = FMath::RandRange(0, 2);

	if (Textures[Index]) {
		MatInstance->SetTextureParameterValue(FName(TEXT("Texture")), Textures[Index]); // ���ָ����material
		CloudPlane->SetMaterial(0, MatInstance); // �������ò���
	}
}

void ACloud::DisplayScore()
{
	MuffinCharacter->InCreaseScore();
	ScoreText->SetText(FText::FromString(FString::FromInt(MuffinCharacter->GetScore())));

}

void ACloud::EnableRain()
{
	int Index = FMath::RandRange(0, 2);
	if (Index == 0)
	{
		RainPlane->SetVisibility(true);
		AudioComponent->Activate(true);
	}
}

// Called every frame
void ACloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACloud::NotifyActorBeginOverlap(AActor*OtherActor) 
{
	Super::NotifyActorBeginOverlap(OtherActor); // ���ø��ຯ��

	MuffinCharacter=  Cast<AMuffinCharacter>(OtherActor);
	if (MuffinCharacter) {
		MuffinCharacter->Launch();
		DisplayScore();
		UGameplayStatics::PlaySoundAtLocation(this, CloudSound, GetActorLocation());
		FadeOut();
	}
}
