// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayer.h"

// Sets default values
AEnemy::AEnemy()
{
	AIControllerClass = AEnemyAIController::StaticClass();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy::Highlight()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);

}

void AEnemy::Unhighlight()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
}

void AEnemy::OnDead(AActor* DamageCauser)
{
	UE_LOG(LogTemp, Log, TEXT("OnDead"));

}
