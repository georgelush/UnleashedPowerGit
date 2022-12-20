#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class UPawnSensingComponent;

UCLASS()
class SLASH_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	/** <AActor> */
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;
	/**  </AActor> */
	

	/**  <IHitInterface> */
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	/**  </IHitInterfacce> */

private:

	AActor* ChoosePatrolTarget();
	
	/**  AI Behavior */
	void InitializeEnemy();
	void CheckPatrolTarget();
	void CheckCombatTarget();
	void PatrolTimerFinished();
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	void ClearPatrolTimer(); 
	void StartAttackTimer();
	void ClearAttackTimer();
	void MoveToTarget(AActor* Target);
	void SpawnDefaultWeapon();
	

	bool InTargetRange(AActor* Target, double Radius);
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();

	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<class AWeapon> WeaponClass;
	

	UPROPERTY(EditAnywhere, Category = Combat)
	double CombatRadius = 1000.f;


	UPROPERTY(EditAnywhere, Category = Combat)
	double AttackRadius = 200.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double AcceptanceRadius = 50.f;

	// Current patrol target
	FTimerHandle PatrolTimer;
	FTimerHandle AttackTimer;

	UPROPERTY(EditInstanceOnly, Category = "Ai Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditInstanceOnly, Category = "Ai Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 2.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 5.f;

	UPROPERTY(EditAnywhere)
	double PatrolRadius = 250.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrolSpeed = 125.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float DeathLifeSpan = 8.f;

	UPROPERTY()
	class AAIController* EnemyController;

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);  // Callback for OnPawnSeen in UPawnSensingComponent

	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf < class ASoul> SoulClass;

protected:
	/** <AActor> */
	virtual void BeginPlay() override;
	/** </AActor> */

	virtual void Die() override;
	virtual void Attack() override;
	virtual void AttackEnd() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual bool CanAttack() override;

	void SpawnSoul();

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

	
};