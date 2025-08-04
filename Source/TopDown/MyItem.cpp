// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItem.h"
#include "Components/BoxComponent.h"
#include "MyPlayer.h"

// Sets default values
AMyItem::AMyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Script/Engine.StaticMesh'/Game/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_Mace.SM_Mace'"));
	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object);
	}


	BoxComponent->SetupAttachment(Mesh);

	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	BoxComponent->SetCollisionProfileName(TEXT("Item"));
	BoxComponent->SetBoxExtent(FVector(20.f, 20.f, 40.f));

}

void AMyItem::PostInitProperties()
{
	Super::PostInitProperties();
	
}

// Called when the game starts or when spawned
void AMyItem::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyItem::OnCharacterOverlap);
}

void AMyItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlap"));
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(OtherActor);
	if (MyPlayer)
	{
		FName WeaponSocket(TEXT("hand_rSocket"));
		if (MyPlayer->GetMesh()->DoesSocketExist(WeaponSocket))
		{
			AttachToComponent(MyPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);

		}

	}

}

