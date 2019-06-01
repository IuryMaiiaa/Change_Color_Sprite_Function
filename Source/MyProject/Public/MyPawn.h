// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "PaperSpriteComponent.h"
#include "PaperSpriteActor.h"
#include "PaperSprite.h"
#include "PaperFlipbookComponent.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"


UCLASS()
class MYPROJECT_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void UpdateTextureRegions(UTexture2D* Texture, int32 MipIndex, uint32 NumRegions, FUpdateTextureRegion2D* Regions, uint32 SrcPitch, uint32 SrcBpp, uint8* SrcData, bool bFreeData);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		int32 TotalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float DamageTimeInSeconds;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Damage")
		float DamagePerSecond;
	UPROPERTY(VisibleDefaultsOnly) UPaperSpriteComponent *m_shipVisual;

	UFUNCTION(BlueprintCallable)
		UPaperSprite* MyFunction( UPaperSpriteComponent *spriteTest, AActor *pOwner, FColor color1, FColor color2);

	UFUNCTION(BlueprintCallable)
		void MyFunction2();
	
};
