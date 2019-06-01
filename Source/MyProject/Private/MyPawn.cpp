// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "../Public/MyPawn.h"




// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/*
void UpdateTextureRegions(UTexture2D* Texture, int32 MipIndex, uint32 NumRegions, FUpdateTextureRegion2D* Regions, uint32 SrcPitch, uint32 SrcBpp, uint8* SrcData, bool bFreeData)
{
	if (Texture->Resource)
	{
		struct FUpdateTextureRegionsData
		{
			FTexture2DResource* Texture2DResource;
			int32 MipIndex;
			uint32 NumRegions;
			FUpdateTextureRegion2D* Regions;
			uint32 SrcPitch;
			uint32 SrcBpp;
			uint8* SrcData;
		};

		FUpdateTextureRegionsData* RegionData = new FUpdateTextureRegionsData;

		RegionData->Texture2DResource = (FTexture2DResource*)Texture->Resource;
		RegionData->MipIndex = MipIndex;
		RegionData->NumRegions = NumRegions;
		RegionData->Regions = Regions;
		RegionData->SrcPitch = SrcPitch;
		RegionData->SrcBpp = SrcBpp;
		RegionData->SrcData = SrcData;

		ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(
			UpdateTextureRegionsData,
			FUpdateTextureRegionsData*, RegionData, RegionData,
			bool, bFreeData, bFreeData,
			{
			for (uint32 RegionIndex = 0; RegionIndex < RegionData->NumRegions; ++RegionIndex)
			{
				int32 CurrentFirstMip = RegionData->Texture2DResource->GetCurrentFirstMip();
				if (RegionData->MipIndex >= CurrentFirstMip)
				{
					RHIUpdateTexture2D(
						RegionData->Texture2DResource->GetTexture2DRHI(),
						RegionData->MipIndex - CurrentFirstMip,
						RegionData->Regions[RegionIndex],
						RegionData->SrcPitch,
						RegionData->SrcData
						+ RegionData->Regions[RegionIndex].SrcY * RegionData->SrcPitch
						+ RegionData->Regions[RegionIndex].SrcX * RegionData->SrcBpp
						);
				}
			}
			if (bFreeData)
			{
				FMemory::Free(RegionData->Regions);
				FMemory::Free(RegionData->SrcData);
			}
			delete RegionData;
			});
	}
}
*/
UFUNCTION(BlueprintCallable)
UPaperSprite* AMyPawn::MyFunction( UPaperSpriteComponent *spriteTest, AActor *pOwner, FColor color1, FColor color2)
{
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("PixelColor:  %f, %f, %f"), (float)color2.R, (float)color2.G, (float)color2.B));

	
	UPaperSprite* sprite = spriteTest->GetSprite();
	FColor PixelColor;
	FString string;
	
	UTexture2D* MyTexture2D = sprite->GetBakedTexture();
	UTexture2D* Texture =  sprite->GetBakedTexture();

	TextureCompressionSettings OldCompressionSettings = MyTexture2D->CompressionSettings; 
	
	TextureMipGenSettings OldMipGenSettings = MyTexture2D->MipGenSettings; 
	
	bool OldSRGB = MyTexture2D->SRGB;

	MyTexture2D->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	MyTexture2D->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	MyTexture2D->MaxTextureSize = 0;
	MyTexture2D->SRGB = false;
	MyTexture2D->UpdateResource();
	//PF_FloatRGBA
	FColor* FormatedImageData = static_cast<FColor*>(MyTexture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	for (int32 X = 0; X < (int32)MyTexture2D->GetSizeX(); X++)
	{
		for (int32 Y = 0; Y < (int32)MyTexture2D->GetSizeY(); Y++)
		{
			
			PixelColor = FormatedImageData[Y * (int32)MyTexture2D->GetSizeX() + X];
			//color2.A = PixelColor.A;
			//FString string = PixelColor.ToString();
			//if (GEngine)
			//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("PixelColor:  %f, %f"), (float)color1.B, (float)PixelColor.B));
			if (PixelColor.B == color1.B && PixelColor.G == color1.G && PixelColor.R == color1.R)
			{
				FormatedImageData[Y * (int32)MyTexture2D->GetSizeX() + X] = color2;
			}
			
			PixelColor = FormatedImageData[Y * (int32)MyTexture2D->GetSizeX() + X];
			//string = PixelColor.ToString();
			//if (GEngine)
			//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("PixelColor:  %f, %f, %f"), (float)PixelColor.R, (float)PixelColor.G, (float)PixelColor.B));
		}
	}
	MyTexture2D->PlatformData->Mips[0].BulkData.Unlock();

	
	MyTexture2D->UpdateResource();

	//FSpriteAssetInitParameters initParams;
	//initParams.SetTextureAndFill((UTexture2D*)MyTexture2D);
	
	//sprite->InitializeSprite(initParams);

	//Texture->CompressionSettings = OldCompressionSettings;
	//Texture->MipGenSettings = OldMipGenSettings;
	//Texture->SRGB = OldSRGB;
	//Texture->UpdateResource();

	return sprite;
}

void AMyPawn::MyFunction2()
{
}

