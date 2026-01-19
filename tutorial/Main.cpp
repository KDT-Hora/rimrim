//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <imgui.h>
//#include <imgui-SFML.h>
//
//#include "Input.h"
//
//int main()
//{
//
//	unsigned int width = 640 * 2;
//	unsigned int height = 360 * 2;
//
//
//	sf::RenderWindow* window = 
//		new sf::RenderWindow(sf::VideoMode({ width,height }), "Tutorials");
//	
//	std::cout << "Window create" << std::endl;
//
//	window->setFramerateLimit(60);
//	if (ImGui::SFML::Init(*window) == false)
//	{
//		std::cout << "ImGui Init error!" << std::endl;
//	}
//	
//	//	Dockingの有効化
//	ImGuiIO& io = ImGui::GetIO();
//	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		//	ドッキング有効化
//
//	// スタイル調整
//	ImGui::StyleColorsDark();
//	ImGuiStyle& style = ImGui::GetStyle();
//	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
//		style.WindowRounding = 0.0f;
//		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//	}
//
//	sf::Clock deltaClock;
//
//	//	ここまでがSFMLとGUIの初期設定
//
//	sf::View view(sf::FloatRect({ 0.f, 0.f },{ 800.f, 600.f}));
//
//	sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
//	player.setFillColor(sf::Color::Green);
//	player.setPosition({ 400.f, 300.f });
//
//
//	while (window->isOpen())
//	{
//		while (const std::optional<sf::Event> eventOptional = window->pollEvent())
//		{
//			const sf::Event& event = *eventOptional;
//
//			ImGui::SFML::ProcessEvent(*window, event);
//			InputManager::Instance().update(event);
//
//
//
//			if (event.is<sf::Event::Closed>())
//			{
//				std::cout << "Window close" << std::endl;
//				window->close();
//			}
//		}
//
//		//	ここに通常の処理を記載
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
//			view.move({ -5.f, 0.f });
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
//			view.move({ 5.f, 0.f });
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
//			view.move({0.f, -5.f});
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
//			view.move({ 0.f, 5.f });
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
//			view.zoom(0.98f);  // ズームイン
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
//			view.zoom(1.02f);  // ズームアウト
//
//
//		if (InputManager::Instance().isKeyHeld(sf::Keyboard::Key::Right))
//		{
//			std::cout << "Press RIGHT" << std::endl;
//		}
//
//		//	ImGui
//		ImGui::SFML::Update(*window,deltaClock.restart());
//
//		//	ドッキングレイアウト指定をここで可能
//		ImGui::DockSpaceOverViewport(0,ImGui::GetMainViewport());
//
//		ImGui::Begin("Hello from ImGui");
//		ImGui::Text("SFML 3.0.2 + ImGui");
//		if (ImGui::Button("Exit")) {
//			std::cout << "Window close for ImGui button" << std::endl;
//			window->close();
//		}
//		ImGui::End();
//
//		//	ウィンドウ一つ単位
//		// BeginとEndでくくっている間がその範囲の中が、一つのウィンドウになる
//		ImGui::Begin("second window");
//		ImGui::Text("test window");
//		if (ImGui::Button("Test")) {
//			std::cout << "Press Test button" << std::endl;
//		}
//
//		//	カラーボックス表示
//		//	変更も可能
//		static ImVec4 color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // 初期色：赤
//		ImGui::ColorEdit4("Color", (float*)&color);
//		//	色の表示飲み
//		ImGui::ColorButton("ColorBox", color);
//
//		ImGui::End();
//
//		//	デモウィンドウの表示メソッド
//		//	基本いらない
//	//	ImGui::ShowDemoWindow();
//
//		//	------------------------------------
//
//		window->clear();
//		ImGui::SFML::Render(*window);
//
//		window->setView(view);
//		window->draw(player);
//
//		window->display();
//
//
//		InputManager::Instance().reset();
//	}
//
//	ImGui::SFML::Shutdown();
//
//	delete window;
//
//	return 0;
//}
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "ECS/ECSManager.h"
#include "ECS/ECSConfig.h"
#include "Context/SystemContext.h"
#include "ECS/DebugAPI.h"
#include "ECS/Component/Components.h"

#include "Game/GameSession.h"
#include "System/Scene/SceneManager.h"

//	最初のシーンの呼び出し
#include "System/Scene/Title/TitleScene.h"

int main() {

	unsigned int width = 640 * 2;
	unsigned int height = 360 * 2;

	sf::RenderWindow* window =
		new sf::RenderWindow(sf::VideoMode({ width,height }), "Tutorials");
	std::cout << "Window create" << std::endl;

	engine::SystemContext context(*window);
	game::GameSession gameSession;
	gameSession.Init(context);
	SceneManager::Instance().SetGameSession(&gameSession);
	SceneManager::Instance().RequestChange<TitleScene>();
	SceneManager::Instance().Init();


	//	---------------------------
	//	ECS設定


	//	エンティティ１作成
//	auto e1 = ecs.CreateEntity();
//	//	コンポーネントを追加
//	ecs.AddComponent<TransformComponent>(e1, TransformComponent{ {100.f,100.f}, 0.f, {1.f,1.f} });
//	ecs.AddComponent<CircleShapeComponent>(e1, CircleShapeComponent(30.f, sf::Color::Red));
//	ecs.AddComponent<MoveValueComponent>(e1, MoveValueComponent{});
//
//	//	テスト用エンティティ
//	auto e2 = ecs.CreateEntity();
//	ecs.AddComponent<GridPositionComponent>(e2, GridPositionComponent{10,10});
//	ecs.AddComponent<DebugRendererComponent>(e2, DebugRendererComponent{ sf::Color::Cyan });
//
//	//	エンティティをマップに登録
//	gameSession.DebugAddEntityToMap(e2, 10, 10);


	//	-----------------------------------------
	
	window->setFramerateLimit(60);
	if (ImGui::SFML::Init(*window) == false)
	{
		std::cout << "ImGui Init error!" << std::endl;
	}
	//	Dockingの有効化
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		//	ドッキング有効化
	


	sf::Clock clock;
	while (window->isOpen()) {
		sf::Time dt = clock.restart();

	
		while (const std::optional<sf::Event> eventOptional = window->pollEvent()) {
			const sf::Event& event = *eventOptional;

			ImGui::SFML::ProcessEvent(*window, event);

			if (event.is<sf::Event::Closed>())
			{
				std::cout << "Window close" << std::endl;
				window->close();
			}
		}


		window->clear();

		ImGui::SFML::Update(*window, clock.restart());

		//	ウィンドウの端とかにつけるやつ
		//	画面が見たい時はこれをオフにする
		//	切り替えで管理する
	//	ImGuiViewport* id = ImGui::GetMainViewport();
	//	ImGui::DockSpaceOverViewport(id->ID);


		// デバッグ描画 (DebugAPIを使用)
		ImGui::Begin("ECS Inspector");
		// debug.GetAllEntities()... などを呼び出して表示
		// 値の変更は debug.SetComponentValue(...) を呼ぶ
		ImGui::End();

		gameSession.Update();

		ImGui::SFML::Render(*window);
		window->display();

	
	}
	ImGui::SFML::Shutdown();
	delete window;

	return 0;
}