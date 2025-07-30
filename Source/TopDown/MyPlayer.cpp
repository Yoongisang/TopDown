// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CharacterAnim.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->SetRelativeRotation(FRotator(-50.f, 45.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;


}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	CharacterAnim = Cast<UCharacterAnim>(GetMesh()->GetAnimInstance());
	CharacterAnim->OnMontageEnded.AddDynamic(this, &AMyPlayer::OnAttackMontageEnded);
	CharacterAnim->OnAttackHit.AddUObject(this, &AMyPlayer::OnAttackHit);

}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyPlayer::Attack()
{
	if (bIsAttacking)
		return;

	CharacterAnim->PlayAttackMontage();

	bIsAttacking = true;

}

void AMyPlayer::OnAttackHit()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 250.f;
	float AtttackRadius = 50.f;
	float HalfHeight = AttackRange * 0.5 + AtttackRadius;

	FVector Forward = GetActorForwardVector() * AttackRange;
	FQuat Rot = FRotationMatrix::MakeFromZ(Forward).ToQuat();

	bool Result = GetWorld()->SweepSingleByChannel(OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + Forward,
		Rot,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeCapsule(AtttackRadius, HalfHeight),
		Params);

	FVector Center = GetActorLocation() + Forward * 0.5f;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Forward).ToQuat();

	FColor DrawColor = Result ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AtttackRadius, Rot, DrawColor, false, 2.f);

	if (Result && HitResult.GetActor())
	{
		auto Enemy = Cast<AEnemy>(HitResult.GetActor());
		if (Enemy)
		{
			UGameplayStatics::ApplyDamage(Enemy, 10.f, GetController(), nullptr, NULL);
		}
		
	}

}

void AMyPlayer::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;
}

float AMyPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Log, TEXT("Damage : %f"), Damage);
	return 0.0f;
}
