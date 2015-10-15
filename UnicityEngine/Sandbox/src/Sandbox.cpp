#include <unicity.h>
#include <app/Application.h>

using namespace u_engine;
using namespace graphics;
using namespace maths;


#define WIDTH 1280
#define HEIGHT 720


class Game : public Application {

private:

	Layer* layer;
	Label* fps;
	Sprite* sprite;
	Shader* shader;
	Mask* mask;

public:

	Game()
		:Application("Test App", WIDTH, HEIGHT) { }

	~Game() {

		delete layer;
	}

	UE_void init() override {

		UNICITY_STARTUP(" dev00.00.06 "); //Base format: _devxx.xx.xx_ -> Indent according to this setting
		Application::init();

		FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);
		shader = ShaderFactory::DefaultShader();
		layer = new Layer(new BatchRenderer2D(tvec2<UE_uint>(WIDTH, HEIGHT)), shader, mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layer->renderer2D->SetRenderTarget(RenderTarget::SCREEN);

		Texture::setFilter(TextureFilter::NEAREST);

		sprite = new Sprite(0.0f, 0.0f, 8, 8, new Texture("Tex", "res/t1.png"));
		layer->add(sprite);

		fps = new Label("", -15.5f, 7.8f, 0xffffffff);
		layer->add(fps);



		Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
		mask = new Mask(new Texture("Mask", "res/mask.png"));
		mask->transform = mat4::translation(vec3(-16.0f, -9.0f, 0.0f)) * mat4::scale(vec3(32, 18, 1));
//		layer->setMask(mask);

		UNICITY_FATAL("Unicity Engine is running...");

	}

	void tick() override {

		fps->text = std::to_string(getFPS()) + " fps";
		UNICITY_INFO(getUPS(), " ups, ", getFPS(), " fps");
	}

	void update() override {
		float speed = 0.5;

		if (window->isKeyPressed(VK_UP))
			sprite->position.y += speed;
		else if (window->isKeyPressed(VK_DOWN))
			sprite->position.y -= speed;
		
		if (window->isKeyPressed(VK_LEFT))
			sprite->position.x -= speed;
		else if (window->isKeyPressed(VK_RIGHT))
			sprite->position.x += speed;


		
        
    }

	void render() override
	{
		layer->render();

	}
};



	int main()
	{
		Game game;
		game.start();
		return 0;
	}
