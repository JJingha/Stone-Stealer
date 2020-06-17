// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Attach.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT05_API UAnimNotify_Attach : public UAnimNotify
{
	GENERATED_BODY()
protected:
	//�����һ��֪ͨ����
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
	UPROPERTY(EditAnywhere)
		FName AnimSocketName;
};
