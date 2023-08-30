// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpaceShip.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComp"));
	RootComponent = SphereCollisionComp;

	ShipStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipStaticMeshComp"));
	ShipStaticMeshComp->SetupAttachment(RootComponent);

	Speed = 300.0f;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	SpaceShipPlayer = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(this,0)); // ��ȡ����
	SetColor();
	
}

void AEnemy::MoveTowardPlayer(float DeltaTime)
{
	// ������ ��ȥ ����λ�� ����õ� ����ָ�����ǵ� ����
	FVector Direction= (SpaceShipPlayer->GetActorLocation() - GetActorLocation()).GetSafeNormal(); // ��λ��
	AddActorWorldOffset(Direction*Speed*DeltaTime, true); // �ƶ�

	// �������ǣ�������ת
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), SpaceShipPlayer->GetActorLocation()));

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveTowardPlayer(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

