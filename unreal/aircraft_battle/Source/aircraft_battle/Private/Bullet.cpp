// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy.h"
#include "Engine/BlockingVolume.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	BulletStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletStaticMeshComp"));
	BulletStaticMeshComp->SetupAttachment(RootComponent);


	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AEnemy* Enemy =Cast<AEnemy>(OtherActor); // 转换为敌人
	if (Enemy) {

		Enemy->OnDead(); //敌人销毁
		
		Destroy(); // 销毁子弹
	}
	else if (Cast<ABlockingVolume>(OtherActor)) {
		Destroy(); // 销毁子弹
	}
}

