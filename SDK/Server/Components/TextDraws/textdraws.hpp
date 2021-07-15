#pragma once

#include <types.hpp>
#include <values.hpp>
#include <player.hpp>
#include <netcode.hpp>
#include <plugin.hpp>

/// Text draw's text alignment
enum TextDrawAlignment {
	TextDrawAlignment_Default,
	TextDrawAlignment_Left,
	TextDrawAlignment_Center,
	TextDrawAlignment_Right
};

/// Textdraw's drawing style
enum TextDrawStyle {
	TextDrawStyle_FontBeckettRegular, ///< Font type
	TextDrawStyle_FontAharoniBold, ///< Font type
	TextDrawStyle_FontBankGothic, ///< Font type
	TextDrawStyle_FontPricedown, ///< Font type
	TextDrawStyle_Sprite, ///< TXD sprite
	TextDrawStyle_Preview ///< Model preview
};

/// Text label base interface
struct ITextDrawBase : public IIDProvider {
	/// Get the textdraw's position
	virtual Vector2 getPosition() const = 0;

	/// Set the textdraw's position
	virtual ITextDrawBase& setPosition(Vector2 position) = 0;

	/// Set the textdraw's text
	virtual void setText(const String& text) = 0;
	
	/// Get the textdraw's text
	virtual const String& getText() const = 0;

	/// Set the letter size
	virtual ITextDrawBase& setLetterSize(Vector2 size) = 0;

	/// Get the letter size
	virtual Vector2 getLetterSize() const = 0;

	/// Set the text size
	virtual ITextDrawBase& setTextSize(Vector2 size) = 0;

	/// Get the text size
	virtual Vector2 getTextSize() const = 0;

	/// Set the text alignment
	virtual ITextDrawBase& setAlignment(TextDrawAlignment alignment) = 0;

	/// Get the text alignment
	virtual TextDrawAlignment getAlignment() const = 0;

	/// Set the letters' colour
	virtual ITextDrawBase& setLetterColour(Colour colour) = 0;

	/// Get the letters' colour
	virtual Colour getLetterColour() const = 0;

	/// Set whether the textdraw uses a box
	virtual ITextDrawBase& setUsingBox(bool use) = 0;

	/// Get whether the textdraw uses a box
	virtual bool isUsingBox() const = 0;

	/// Set the textdraw box's colour
	virtual ITextDrawBase& setBoxColour(Colour colour) = 0;

	/// Get the textdraw box's colour
	virtual Colour getBoxColour() const = 0;

	/// Set the textdraw's shadow strength
	virtual ITextDrawBase& setShadow(int shadow) = 0;

	/// Get the textdraw's shadow strength
	virtual int getShadow() const = 0;

	/// Set the textdraw's outline
	virtual ITextDrawBase& setOutline(int outline) = 0;

	/// Get the textdraw's outline
	virtual int getOutline() const = 0;

	/// Set the textdraw's background colour
	virtual ITextDrawBase& setBackColour(Colour colour) = 0;

	/// Get the textdraw's background colour
	virtual Colour getBackColour() const = 0;

	/// Set the textdraw's drawing style
	virtual ITextDrawBase& setStyle(TextDrawStyle style) = 0;

	/// Get the textdraw's drawing style
	virtual TextDrawStyle getStyle() const = 0;

	/// Set whether the textdraw is proportional
	virtual ITextDrawBase& setProportional(bool proportional) = 0;

	/// Get whether the textdraw is proportional
	virtual bool isProportional() const = 0;

	/// Set whether the textdraw is selectable
	virtual ITextDrawBase& setSelectable(bool selectable) = 0;

	/// Get whether the textdraw is selectable
	virtual bool isSelectable() const = 0;

	/// Set the textdraw's preview model
	virtual ITextDrawBase& setPreviewModel(int model) = 0;

	/// Get the textdraw's preview model
	virtual int getPreviewModel() const = 0;

	/// Set the textdraw's preview rotation
	virtual ITextDrawBase& setPreviewRotation(GTAQuat rotation) = 0;

	/// Get the textdraw's preview rotation
	virtual GTAQuat getPreviewRotation() const = 0;

	/// Set the textdraw's preview vehicle colours
	virtual ITextDrawBase& setPreviewVehicleColour(int colour1, int colour2) = 0;

	/// Get the textdraw's preview vehicle colours
	virtual std::pair<int, int> getPreviewVehicleColour() const = 0;

	/// Set the textdraw's preview zoom factor
	virtual ITextDrawBase& setPreviewZoom(float zoom) = 0;

	/// Get the textdraw's preview zoom factor
	virtual float getPreviewZoom() const = 0;

	/// Restream the textdraw
	virtual void restream() = 0;
};

struct ITextDraw : public ITextDrawBase {
	/// Show the textdraw for a player
	virtual void showForPlayer(IPlayer& player) = 0;

	/// Hide the textdraw for a player
	virtual void hideForPlayer(IPlayer& player) = 0;

	/// Get whether the textdraw is shown for a player
	virtual bool isShownForPlayer(const IPlayer& player) const = 0;
};

struct IPlayerTextDraw : public ITextDrawBase {
	/// Show the textdraw for its player
	virtual void show() = 0;

	/// Hide the textdraw for its player
	virtual void hide() = 0;

	/// Get whether the textdraw is shown for its player
	virtual bool isShown() const = 0;
};

struct TextDrawEventHandler {
	virtual void onTextDrawSelectionCancel(IPlayer& player) {}
	virtual void onTextDrawClick(IPlayer& player, ITextDraw& td) {}
	virtual void onPlayerTextDrawClick(IPlayer& player, IPlayerTextDraw& td) {}
};

static const UUID TextDrawsPlugin_UUID = UUID(0x9b5dc2b1d15c992a);
/// The textdraw plugin which is a global textdraw pool
struct ITextDrawsPlugin : public IPlugin, public IPool<ITextDraw, MAX_GLOBAL_TEXTDRAWS> {
	PROVIDE_UUID(TextDrawsPlugin_UUID);

	/// Get the textdraw event dispatcher
	virtual IEventDispatcher<TextDrawEventHandler>& getEventDispatcher() = 0;

	/// Create a new textdraw with some text
	virtual ITextDraw* create(Vector2 position, const String& text) = 0;

	/// Create a new textdraw with some preview model
	virtual ITextDraw* create(Vector2 position, int model) = 0;
};

static const UUID PlayerTextDrawData_UUID = UUID(0xbf08495682312400);
/// The textdraw player data which is a player textdraw pool
struct IPlayerTextDrawData : public IPlayerData, public IPool<IPlayerTextDraw, MAX_PLAYER_TEXTDRAWS> {
	PROVIDE_UUID(PlayerTextDrawData_UUID);

	/// Begin selecting textdraws for the player
	virtual void beginSelection(Colour highlight) = 0;

	/// Get whether the player is selecting textdraws
	virtual bool isSelecting() const = 0;

	/// Stop selecting textdraws for the player
	virtual void endSelection() = 0;

	/// Create a new textdraw with some text
	virtual IPlayerTextDraw* create(Vector2 position, const String& text) = 0;

	/// Create a new textdraw with some preview model
	virtual IPlayerTextDraw* create(Vector2 position, int model) = 0;
};
