// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Camera/CameraActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#define ECC_Projectile ECC_GameTraceChannel1

// Sets default values
AProjectileBase::AProjectileBase()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	RootComponent = collisionComponent;

	collisionComponent->SetCollisionObjectType(ECC_Projectile);
	collisionComponent-> SetCollisionResponseToChannel(ECC_Projectile, ECR_Ignore);

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	projOwner = GetOwner();
	projMovement = FindComponentByClass<UProjectileMovementComponent>();
	projMovement->Activate();

	// set OnHit function to be called when the projectile hits something
	if (collisionComponent)
	{
		collisionComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
		collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnOverlap);
	}
	if (!InstigatorController)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Projectile Spawned"));
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	if (!OtherActor || OtherActor == this || OtherActor == projOwner) return;
	if (actorsToIgnore.Contains(OtherActor)) return;
	actorsToIgnore.Add(OtherActor);
	
	
	UGameplayStatics::ApplyDamage(OtherActor, Damage, InstigatorController, this, nullptr);

	OnProjectileImpact(Hit);

	if (destroyOnHit)
		Destroy();
}

void AProjectileBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this || OtherActor == projOwner) return;
	if (actorsToIgnore.Contains(OtherActor)) return;
	actorsToIgnore.Add(OtherActor);


	UGameplayStatics::ApplyDamage(OtherActor, Damage, InstigatorController, this, nullptr);

	OnProjectileImpact(SweepResult);

	if (destroyOnHit)
		Destroy();
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

