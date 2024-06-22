# TheMage_Source_Portfolio

플레이 영상 유튜브 링크: https://youtu.be/K2QGk7OlUCc

itch.io 데모 게임실행: https://12equal34.itch.io/the-mage-demo

그래픽 디자인 및 프로그래밍은 모두 제가 제작하였습니다.

사운드 효과는 GDC Free Audio Bundles 를 활용하였습니다.

## Ideas
TheMage는 던전앤파이터의 조작키, 기본 공격의 콤보 방식과 2D 애니메이션 방식을 참조하였습니다.
겟앰프드에서는 3D 플랫폼 환경과 카메라 뷰를 참조하였습니다. The Mage의 게임 환경 그래픽은 바람의나라의 픽셀 그래픽을 참조했습니다.
몬스터가 죽으면 떨어지는 동전 모션과 몬스터인 악어를 귀엽게 만들려는 시도는 메이플스토리를 참조했습니다.

전투 방식을 구현하면서 느낀 점은 키보드의 입력, 캐릭터의 애니메이션, 공격 판정이 서로 연결되어 있음을 느꼈습니다.
이러한 전투 조작이 액션 게임에서 가장 중요한 부분 중 하나라고 생각하여 가장 신경쓰고, 이를 PaperAnim 폴더에 정리하였습니다.
그리고 몬스터의 AI 구현은 몬스터를 사냥하는 재미를 담당하기 때문에 어떻게 구현해야 좋을까 생각하면서, 이를 Monster 폴더에 정리하였습니다.

제가 만든 게임은 3D 월드에서 캐릭터들이 움직이지만, 캐릭터들은 2D 페이퍼 그림의 형태를 가졌습니다.
그래서 충돌 판정에 대한 고민이 많았습니다. 결과적으로 캐릭터들이 3D 월드에서 움직일 때, 환경과의 충돌은 Capsule 충돌체를 사용하였고
몬스터와의 피격판정은 UPaperSprite의 XZ 평면 상 그림의 외형을 따오고 Y축은 얇은 폭을 가진 폴리곤 충돌체를 사용하였습니다.

1. 주인공인 마법사가 펀치 공격을 할 때, 몬스터인 악어가 맞는 상황
2. 악어가 마법사에 접촉하여 접촉 데미지를 가하는 상황
3. 함정 트랩에 마법사가 부딪혔을 때, 접촉 데미지를 가하는 상황

위와 같은 전투 경험에 관련해서 각각의 페이퍼 그림이 시각적으로 정말로 서로 접촉된 상황에 대해서만 충돌 판정을 하는 것이
불쾌하지 않고 2.5D 게임의 이질감을 줄이는 방법이라 생각했습니다.

원래는 모든 캐릭터들의 피격 판정을 위한 충돌체를 Capsule로 사용했을 때, 어느 위치에서 몬스터가 맞고, 내 캐릭터가 피격받는 지 헷갈리는 상황이 많아서
2.5D 게임은 괜히 안 만드는 것이 아니구나 하며 생각하다가 위와 같이 해결한 것입니다. 또한 캐릭터의 현재 3D 월드 내에서의 위치를 보여주는 UPositionGuideComponent를 만들어서 캐릭터의 아래 방향으로 레이트레이싱을 하여 위치를 알려주는 역할을 하였습니다.
기존의 참고 자료가 없는 2.5D 액션 게임이란 새로운 시도를 하면서 어떻게 하면 이질감 없는 게임을 만들 수 있을지 고민했던 것 같습니다.

2D 애니메이션으로 PaperZD 라는 플러그인을 사용할 수 있었지만,
저는 직접 PaperAnim 시스템을 만들어서 2D 애니메이션과 이에 연결되는 이벤트(사운드, 대쉬, 스킬생성) 발생을 가능하게 만들었습니다.
그렇게 함으로써 애니메이션 관련 에셋들을 한 군데에서 관리할 수 있고, 애니메이션과 이벤트 효과를 에디터에서 손쉽게 변경할 수 있도록 만들었습니다.

## Core Folders
1. **PaperAnim** : 2D 캐릭터의 애니메이션을 담당합니다.
2. **Monster**   : 몬스터의 AI를 담당합니다.

## PaperAnim
>엔진 내의 **APaperCharacter**는 **UPaperFlipbookComponent**를 통해 2d Animation을 애니메이션의 전통적인 Flipbook 방법으로 구현합니다.
>이때 **UPaperFlipbookComponent**의 **TickFlipbook** 메서드를 사용합니다.
>**TickFlipbook**에서 **SetPlaybackPosition** 메서드를 사용하여 현재 캐릭터의 스프라이트(**UPaperFlipbook**)를 갱신합니다.

**APaperAnimCharacter**는 **APaperCharacter**를 상속하고 기존의 **UPaperFlipbookComponent**의 **TickFlipbook**를 사용하지 않고,
새롭게 **UPaperAnimPlayer**를 사용하여 **TickPlayback** 메서드를 사용하여 애니메이션을 재생합니다. 즉 재생 책임을 **UPaperAnimPlayer**로 전가하였습니다.

**UPaperAnimPlayer**는 **UPaperFlipbookComponent**과 다르게 time 단위가 아닌 frame 단위로 증분하여 재생합니다.
이유는 각 frame key에 해당하는 현재 캐릭터의 스프라이트(**UPaperFlipbook**)가 끝나거나 시작되었을 때, 이벤트 또는 **PlayFrameEffects** 메서드 호출을 발생하기 위함입니다.

![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/4f8939c0-4364-41fb-a024-86e9c14468e9)

**PlayFrameEffects** 메서드는 현재 캐릭터의 스프라이트가 변경되었을 때, frame key에 해당하는 **UPaperAnimAsset**의 컨테이너 내 원소의 **UPaperAnimFrameEffect::Play()** 메서드를 호출합니다.
이를 통해 스킬의 스폰, 캐릭터의 질주, 주먹 공격 도중의 방향키 입력으로 인한 이동, 사운드 발생 등을 구현할 수 있었습니다.

![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/351c333c-35cc-4554-8f5e-59741507d112)

타 프로젝트에서 주로 사용하는 **PaperZD** 플러그인(2d animation)을 사용하지 않은 이유는 애니메이션 에셋 관리가 불편했기 때문입니다.
그래서 **UPaperAnimAsset**을 통해 다음과 같이 한 곳에서 애니메이션을 관리할 수 있도록 했습니다.

![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/f1b9f433-4842-43ac-bf3e-1e6f7efa7ccc)

또한 **PaperZD**의 애니메이션 그래프가 복잡하고 불편하다고 느꼈습니다.
이를 **UFUNCTION(BlueprintNativeEvent) CalculateAnimation** 메서드를 통해 블루프린트 노드를 활용하면 더 단순하다고 생각했습니다.

![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/48f0513b-9d8d-4362-9566-522201ad76a4)

## Monster
게임 내의 몬스터는 **AMonsterCharacter**를 상속받습니다.
**AMonsterCharacter**는 몬스터의 AI를 담당하는 **UMonsterComponent**를 갖고 있습니다.
**UMonsterComponent**는 **UMonsterBrain**(판단), **UMonsterSight**(레이트레이싱 인식), **UMonsterSkin**(충돌 인식) 객체를 하나씩 갖습니다.
상속을 통해 각각의 기관들의 능력을 바꿀 수 있습니다.

**UMonsterSight**를 통해 주변에 적이 있는지 판단합니다.

![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/41ce97a9-f784-498e-9937-f8eb922c21f0)
![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/84ddf1e1-16a2-416a-badc-2495b6bf60ec)

**UMonsterSkin**을 통해 적에게 가하는 접촉 피해 관련 데이터들을 설정할 수 있습니다.

![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/b03d4a13-92f5-40de-a5ca-dccc38604dbc)

**UMonsterBrain**은 정확히 AI의 역할을 하게 됩니다.
**UMonsterSight**와 **UMonsterSkin**로부터 축적된 인식 데이터들로부터 분석 및 판단하여 행동(Behaviors)을 결정합니다.

![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/4c3838f2-107a-431b-809d-34304947d7ab)
---
![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/a29256f6-cd11-4c5f-86f2-76b93e996996)
---
![image](https://github.com/12equal34/TheMage_Source_Portfolio/assets/109350254/95912f46-a941-456b-bc2f-3e764bc2aeda)


