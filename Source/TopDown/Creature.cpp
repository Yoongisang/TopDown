// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"
#include "CharacterInfo.h"
#include "CharacterAnim.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HpBarUserWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ACreature::ACreature()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UHpBarUserWidget> UW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));
	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(300.f, 20.f));
		HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));

	}

	CharacterInfo = CreateDefaultSubobject<UCharacterInfo>(TEXT("CharacterInfo"));



}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterAnim = Cast<UCharacterAnim>(GetMesh()->GetAnimInstance());
	CharacterAnim->OnMontageEnded.AddDynamic(this, &ACreature::OnAttackMontageEnded);
	CharacterAnim->OnAttackHit.AddUObject(this, &ACreature::OnAttackHit);

	auto HpWidget = Cast<UHpBarUserWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(CharacterInfo);
	}
	

}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACreature::Attack()
{
	if (bIsAttacking)
		return;

	CharacterAnim->PlayAttackMontage();

	bIsAttacking = true;
}

void ACreature::OnAttackHit()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 250.f;
	float AtttackRadius = 50.f;
	float HalfHeight = AttackRange * 0.5f + AtttackRadius;

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
		auto Other = Cast<ACreature>(HitResult.GetActor());
		if (Other)
		{
			UGameplayStatics::ApplyDamage(Other, 10.f, GetController(), nullptr, NULL);
		}

	}
}

float ACreature::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CharacterInfo->UpdateHp(Damage);

	if (CharacterInfo->Status == ECharacterStatus::DEATH)
		OnDead(DamageCauser);

	return Damage;
}


void ACreature::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;
}

