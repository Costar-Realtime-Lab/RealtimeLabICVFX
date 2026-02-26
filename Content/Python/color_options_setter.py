import unreal

menus = unreal.ToolMenus.get()
toolbar_menu = menus.find_menu("LevelEditor.LevelEditorToolBar.PlayToolBar")

# Toolbar Entry Def
@unreal.uclass()
class ColorPipelineTool_MenuEntry(unreal.ToolMenuEntryScript):
    def init_as_toolbar_button(self):
        self.data.menu = toolbar_menu.menu_name
        self.data.advanced.entry_type = unreal.MultiBlockType.TOOL_BAR_COMBO_BUTTON
        self.data.icon = unreal.ScriptSlateIcon("EditorStyle", "TextureEditor.RedChannel")
        self.data.advanced.style_name_override = "CalloutToolbar"

# Set sRGB Entry Def
@unreal.uclass()
class sRGBMenuEntry(unreal.ToolMenuEntryScript):

    use_srgb = unreal.uproperty(bool)

    @unreal.ufunction(override=True)
    def execute(self, context):
        selected_assets = unreal.EditorUtilityLibrary.get_selected_assets()
        
        if not selected_assets:
            unreal.log_error("No assets selected.")
        else:
            for asset in selected_assets:
                if isinstance(asset, unreal.Texture):
                    asset.set_editor_property("srgb", self.use_srgb)
                    unreal.log_warning(f"Set sRGB {self.use_srgb} on {asset.get_name()}")
                else:
                    unreal.log_error("Selection is not texture.")

# Set ColorSpace Entry Def
@unreal.uclass()
class ColorSpaceMenuEntry(unreal.ToolMenuEntryScript):

    color_space = unreal.uproperty(unreal.TextureColorSpace)

    @unreal.ufunction(override=True)
    def execute(self, context):
        selected_assets = unreal.EditorUtilityLibrary.get_selected_assets()

        if not selected_assets:
            unreal.log_error("No assets selected.")
        else:
            for asset in selected_assets:
                if isinstance(asset, unreal.Texture):
                    asset.source_color_settings.set_editor_property("color_space", self.color_space)
                    unreal.log_warning(f"Applied {self.color_space.name} to {asset.get_name()}")
                else:
                    unreal.log_error("Selection is not texture.")

# Set Encoding Override Entry Def
@unreal.uclass()
class EncodingOverrideMenuEntry(unreal.ToolMenuEntryScript):
    encoding_override = unreal.uproperty(unreal.TextureSourceEncoding)

    @unreal.ufunction(override=True)
    def execute(self, context):
        selected_assets = unreal.EditorUtilityLibrary.get_selected_assets()

        if not selected_assets:
            unreal.log_error("No assets selected.")
        else:
            for asset in selected_assets:
                if isinstance(asset, unreal.Texture):
                    asset.source_color_settings.set_editor_property("encoding_override", self.encoding_override)
                    unreal.log_warning(f"Applied {self.encoding_override.name} to {asset.get_name()}")
                else:
                    unreal.log_error("Selection is not texture.")

def Run():
    # Create Toolbar Entry
    cpt_entry = ColorPipelineTool_MenuEntry()
    cpt_entry.init_as_toolbar_button()
    cpt_entry.init_entry(
        owner_name=toolbar_menu.menu_name,                
        menu=toolbar_menu.menu_name,          
        section="",                         
        name="ColorPipelineToolMenuEntry",       
        label="Color Pipeline",            
        tool_tip="Aye Eye."        
    )
    cpt_entry.register_menu_entry()

    # Create Menu under Toolbar Entry
    cpt_menu = menus.register_menu(
        f"{toolbar_menu.menu_name}.ColorPipelineToolMenuEntry", 
        "",                                         
        unreal.MultiBoxType.MENU,                  
        False                                    
    )

    # Create SetsRGB Menu & Entries
    sRGB_menu = cpt_menu.add_sub_menu(cpt_menu.menu_name, "", "SetsRGB", "Set sRGB", "")

    sRGB_choices = [True, False]
    for choice in sRGB_choices:
        sRGB_entry = sRGBMenuEntry()
        sRGB_entry.init_entry(
            owner_name=sRGB_menu.menu_name,
            menu=sRGB_menu.menu_name,
            section="",
            name=str(choice),
            label=str(choice),
        )
        sRGB_entry.use_srgb = choice
        if choice:
            sRGB_entry.data.icon = unreal.ScriptSlateIcon(style_set_name="UMGStyle", style_name="ClassThumbnail.CheckBox", small_style_name="ClassThumbnail.CheckBox")
        else:
            sRGB_entry.data.icon = unreal.ScriptSlateIcon(style_set_name="UMGStyle", style_name="ClassThumbnail.SafeZone", small_style_name="ClassThumbnail.CheckBox")
        sRGB_entry.register_menu_entry()

    # Create SetColorSpace Menu & Entries
    colorspace_menu = cpt_menu.add_sub_menu(cpt_menu.menu_name, "", "SetColorSpace", "Set Color Space", "")
    
    for color_space in unreal.TextureColorSpace:
        color_space_entry = ColorSpaceMenuEntry()

        color_space_entry.init_entry(
            owner_name=colorspace_menu.menu_name,
            menu=colorspace_menu.menu_name,
            section="",
            name=color_space.name,
            label=color_space.name,
        )
        color_space_entry.color_space = color_space
        color_space_entry.register_menu_entry()
        color_space_entry.data.icon = unreal.ScriptSlateIcon(style_set_name="UMGStyle", style_name="Palette.Icon", small_style_name="Palette.Icon.Small")

    # Create EncodingOverride Menu & Entries
    encoding_override_menu = cpt_menu.add_sub_menu(cpt_menu.menu_name, "", "SetEncodingOverride", "Set Encoding Override", "")

    for encoding_override in unreal.TextureSourceEncoding:
        encoding_override_entry = EncodingOverrideMenuEntry()

        encoding_override_entry.init_entry(
            owner_name=encoding_override_menu.menu_name,
            menu=encoding_override_menu.menu_name,
            section="",
            name=encoding_override.name,
            label=encoding_override.name,
        )
        encoding_override_entry.encoding_override = encoding_override
        encoding_override_entry.register_menu_entry()
        encoding_override_entry.data.icon = unreal.ScriptSlateIcon(style_set_name="UMGStyle", style_name="ClassThumbnail.CircularThrobber", small_style_name="ClassThumbnail.CircularThrobber")

    # Force Refresh
    menus.refresh_all_widgets()