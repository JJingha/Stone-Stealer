// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify_Attach.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "CollisionQueryParams.h"
#include "Engine/EngineTypes.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <DrawDebugHelpers.h>
#include "Monster_Character.h"
#include "Weapons/Weapon_Sword.h"

void UAnimNotify_Attach::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APawn* _Pawn = Cast<APawn>(MeshComp->GetOwner());// MeshComp->GetOwner()���׹Ǽܵ�ӵ���ߣ����꣩
	AController* Controller = _Pawn ? _Pawn->GetController() : nullptr;//��ȡһ�µ�ǰ���������ߵĿ�����

	if (!MeshComp->GetOwner() || !Controller)
	{
		return;
	}
	AAIController* Cont = Cast<AAIController>(Controller);
	if (Cont)
	{
		int32 Randoms = FMath::FRandRange(0, 2);
		//UE_LOG(LogTemp, Log, TEXT("========%d"),Randoms);
	    Cont->GetBlackboardComponent()->SetValueAsInt(TEXT("Random"),Randoms);
	}
	//���μ��
	FVector StartPos = MeshComp->GetSocketLocation(AnimSocketName);//�ӹǼ�����ϻ�ùǼ�λ�ã���Ӧ�Ǽ�����

	TArray<FHitResult> Hits;

	FCollisionShape Shape;
	Shape.ShapeType = ECollisionShape::Sphere;
	Shape.Sphere.Radius = 30;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(MeshComp->GetOwner());
	
	FCollisionObjectQueryParams ObjParams;
	ObjParams.AddObjectTypesToQuery(ECC_Pawn);
	//UE_LOG(LogTemp, Log, TEXT("  ====fasdf"));
	//DrawDebugLine(MeshComp->GetWorld(), StartPos, StartPos+FVector::UpVector*200, FColor::Red);
	if (MeshComp->GetWorld()->SweepMultiByObjectType(Hits, StartPos, StartPos, FQuat(), ObjParams, Shape, Params))
	{
		//UE_LOG(LogTemp, Log, TEXT("  asdfasdf"));

		for (auto Hit : Hits)
		{
			APawn* Pawn = Cast<APawn>(Hit.Actor);
			if (Pawn)
			{
				FPointDamageEvent Event;//����һ�����˺�
										//controller�����ߣ�_Pawn�����ߣ�Event�˺�����
				//if (true)
				//{

				//}
				
				//AMonster_Character* monster = Cast<AMonster_Character>(_Pawn);
				//if (monster)
				//{
				//	Pawn->TakeDamage(0, Event, Controller, monster->GetHoldSword());//���������˺���������
				//}
				Pawn->TakeDamage(FMath::FRandRange(5,10), Event, Controller, _Pawn);//���������˺���������
				return;
			}
		}
	}
}
