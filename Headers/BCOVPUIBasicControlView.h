//
// BCOVPUIBasicControlView.h
// BCOVPUI
//
// Copyright (c) 2015 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>

#import "BCOVPUICommon.h"

@class BCOVPUISlider;
@class BCOVPUIControlLayout;

/** The option to indicate that control height is the itemSize's height */
extern const CGFloat kBCOVPUIControlHeightItemSize;
/** The option to indicate that control height is two times of itemSize's height */
extern const CGFloat kBCOVPUIControlHeightItemSizeDouble;


/** Possible controls components */
typedef NS_OPTIONS(NSUInteger, BCOVPUIBasicComponents){

    /** No components. */
    BCOVPUIBasicComponentNone                 = 0,

    /** Playback button. */
    BCOVPUIBasicComponentButtonPlayback       = 1 << 0,

    /** Jumpback button. */
    BCOVPUIBasicComponentButtonJumpBack       = 1 << 1,

    /** Closed Caption Button. */
    BCOVPUIBasicComponentButtonClosedCaption  = 1 << 2,

    /** Screen Mode button. */
    BCOVPUIBasicComponentButtonScreenMode     = 1 << 3,

    /** Current time label. */
    BCOVPUIBasicComponentLabelCurrentTime     = 1 << 4,

    /** Time separator label. */
    BCOVPUIBasicComponentLabelTimeSeparator   = 1 << 5,

    /** Duration label. */
    BCOVPUIBasicComponentLabelDuration        = 1 << 6,

    /** Progress slider. */
    BCOVPUIBasicComponentSliderProgress       = 1 << 8,

    /** External route (airplay) button. */
    BCOVPUIBasicComponentViewExternalRoute    = 1 << 10,

    /** Live "Go to Live" button. */
    BCOVPUIBasicComponentViewLive             = 1 << 11,

    /** All buttons. */
    BCOVPUIBasicComponentAllButtons          = 0x0000000F,

    /** All labels. */
    BCOVPUIBasicComponentAllLabels           = 0x000000F0,

    /** All components. */
    BCOVPUIBasicComponentAll                 = 0x00000FFF,

    /** Video On Demand components. */
    BCOVPUIBasicComponentStyleVOD            = 0x000005FF,

    /** Live components. */
    BCOVPUIBasicComponentStyleLive           = 0x00000C0D,

    /** Live DVR components. */
    BCOVPUIBasicComponentStyleLiveDVR        = 0x00000D1F,
};


/*
 * Possible control sizes. These can be used by the layout
 * strategy to alter the layout of the view based on its calculated size.
 */
typedef NS_ENUM(NSUInteger, BCOVPUIBasicControlSize)
{
    /** View size determined to be regular  */
    BCOVPUIBasicControlSizeRegular,

    /** View size determined to be compact **/
    BCOVPUIBasicControlSizeCompact
};


/**
 * This block is used by the controls view to generate auto layout constraints.
 * This block will be called under various circumstances like a change of
 * BCOVPUIBasicControlSize, BCOVPUIVideoType, and controls view frame along
 * with the availability of external screen routes and substitles.
 *
 * @param containerView The controls view.
 * @param size The size of the controls view.
 * @param type The video type.
 * @param controlLayout The controls layout used.
 *
 * @return An array of autolayout constraints.
 */
typedef NSArray* (^BCOVPUIControlLayoutStrategy)(UIView *containerView, BCOVPUIBasicControlSize size, BCOVPUIVideoType type, BCOVPUIControlLayout *controlLayout);


/**
 * Layout options used to construct a player view. To modify its properties,
 * create a mutable copy (BCOVPUIMutableControlLayout).
 */
@interface BCOVPUIControlLayout : NSObject <NSCopying, NSMutableCopying>

/**
 * Items to layout.
 */
@property (nonatomic, copy, readonly) NSArray *items;

/**
 * Layout block to controlling the layout of elements.
 */
@property (nonatomic, copy, readonly) BCOVPUIControlLayoutStrategy layoutStrategy;

/**
 * The unit size of views.
 */
@property (nonatomic, assign, readonly) CGSize itemSize;

/**
 * The spacing between views.
 */
@property (nonatomic, assign, readonly) CGFloat itemSpacing;

/**
 * The maximum width of the compact controls. If the controls view is wider than
 * this value, the BCOVPUIBasicControlSize will be switched to Regular.  If less wide,
 * it will switch to Compact. If using default layout strategy, it will use this value
 * along with preferredHeightOfControlSizeRegular and preferredHeightOfControlSizeCompact
 * to determine when to switch from single to double line layouts.
 */
@property (nonatomic, assign, readonly) CGFloat maximumWidthOfControlSizeCompact;

/**
 * Determines the intrinsic content height of the controls with the regular size.
 *
 * It can return UIViewNoIntrinsicMetric, If the height is based on a video type.
 * * BCOVPUIVideoTypeVOD: the height is the itemSize's height.
 * * BCOVPUIVideoTypeLive: the height is the itemSize's height.
 * * BCOVPUIVideoTypeLiveDVR: the height is the itemSize's height.
 *
 * It can return kBCOVPUIControlHeightItemSize, if the height is the itemSize's
 * height regardless of video type.
 *
 * It can return kBCOVPUIControlHeightItemSizeDouble, if the height is two times
 * of itemSize's height regardless of video type.
 */
@property (nonatomic, assign, readonly) CGFloat preferredHeightOfControlSizeRegular;

/**
 * Determines the intrinsic content height of the controls with the regular size.
 *
 * It can return UIViewNoIntrinsicMetric, If the height is based on a video type.
 * * BCOVPUIVideoTypeVOD: the height is two times of itemSize's height.
 * * BCOVPUIVideoTypeLive: the height is the itemSize's height.
 * * BCOVPUIVideoTypeLiveDVR: the height is two times of itemSize's height.
 *
 * It can return kBCOVPUIControlHeightItemSize, if the height is the itemSize's
 * height regardless of video type.
 *
 * It can return kBCOVPUIControlHeightItemSizeDouble, if the height is two times
 * of itemSize's height regardless of video type.
 */
@property (nonatomic, assign, readonly) CGFloat preferredHeightOfControlSizeCompact;

/**
 * Initializes a BCOVPUIControlLayout layout with default settings.
 *
 * @param items The UI components used in the layout. You can use
 * +[BCOVPUIBasicControlView componentItemForBasicComponents:].
 *
 * @return An initializes immutable instance.
 */
- (instancetype)initWithItems:(NSArray *)items;

/**
 * Convenience method that returns a strategy that automatically switches layouts
 * based on video type.
 */
+ (BCOVPUIControlLayoutStrategy)defaultAdaptiveLayoutStrategy;

/**
 * Convenience method that returns a strategy that only uses a Video On Demand layout.
 */
+ (BCOVPUIControlLayoutStrategy)layoutStrategyForVideoTypeVOD;

/**
 * Convenience method that returns a strategy that only uses a Live layout.
 */
+ (BCOVPUIControlLayoutStrategy)layoutStrategyForVideoTypeLive;

/**
 * Convenience method that returns a strategy that only uses a Live DVR layout.
 */
+ (BCOVPUIControlLayoutStrategy)layoutStrategyForVideoTypeLiveDVR;

@end

/**
 * A mutable version of BCOVPUIControlLayout. You can create an instance
 * by either calling mutableCopy on BCOVPUIControlLayout or by using -initWithControlLayout:.
 */
@interface BCOVPUIMutableControlLayout : BCOVPUIControlLayout

@property (nonatomic, copy) BCOVPUIControlLayoutStrategy layoutStrategy;
@property (nonatomic, assign) CGSize itemSize;
@property (nonatomic, assign) CGFloat itemSpacing;
@property (nonatomic, assign) CGFloat maximumWidthOfControlSizeCompact;
@property (nonatomic, assign) CGFloat preferredHeightOfControlSizeRegular;
@property (nonatomic, assign) CGFloat preferredHeightOfControlSizeCompact;

/**
 * Initializes a mutable copy of the control layout.
 * @param controlLayout The control layout to make a mutable copy of.
 *
 * @return An initializes instance.
 */
- (instancetype)initWithControlLayout:(BCOVPUIControlLayout *)controlLayout;

@end


/**
 * Basic controls view.
 */
@interface BCOVPUIBasicControlView : UIView

/** The background view for the controls. On iOS 8, this a UIVisualEffectView
 * with dark blur view.  On iOS 7, its just a black view with slight opacity. */
@property (nonatomic, weak, readonly) UIView *backgroundView;

/** The playback button */
@property (nonatomic, weak, readonly) UIButton *playbackButton;

/** The jump back button */
@property (nonatomic, weak, readonly) UIButton *jumpBackButton;

/** The current time (elapsed) label */
@property (nonatomic, weak, readonly) UILabel *currentTimeLabel;

/** The time separator label */
@property (nonatomic, weak, readonly) UILabel *timeSeparatorLabel;

/** The duration label */
@property (nonatomic, weak, readonly) UILabel *durationLabel;

/** The progress slider */
@property (nonatomic, weak, readonly) BCOVPUISlider *progressSlider;

/** The closed caption button */
@property (nonatomic, weak, readonly) UIButton *closedCaptionButton;

/** The screen mode (fullscreen) button */
@property (nonatomic, weak, readonly) UIButton *screenModeButton;

/** The external route (airplay) button */
@property (nonatomic, weak, readonly) MPVolumeView *externalRouteView;

/** The "go to live" button */
@property (nonatomic, weak, readonly) UIButton *liveView;

/** Yes if the closedCaptionButton is visible. No if invisible. */
@property (nonatomic, assign, readonly) BOOL closedCaptionEnabled;

/** Yes if the externalRouteView is visible. No if invisible. */
@property (nonatomic, assign, readonly) BOOL externalRouteEnabled;

/** The layout used organize the controls. */
@property (nonatomic, copy) BCOVPUIControlLayout *layout;

/** The type of video for the current session. */
@property (nonatomic, assign, readonly) BCOVPUIVideoType currentVideoType;

/**
 * Convenience factory method to create controls with the 
 * defaultAdaptiveLayoutStrategy.
 */
+ (instancetype)basicControlViewWithAdaptiveLayout;

/**
 * Convenience factory method to create controls with the
 * layoutStrategyForVideoTypeVOD.
 */
+ (instancetype)basicControlViewWithVODLayout;

/**
 * Convenience factory method to create controls with the
 * layoutStrategyForVideoTypeLive.
 */
+ (instancetype)basicControlViewWithLiveLayout;

/**
 * Convenience factory method to create controls with the
 * basicControlViewWithLiveDVRLayout.
 */
+ (instancetype)basicControlViewWithLiveDVRLayout;

/**
 * Updates all label components with the specified font size.
 *
 * @param fontSize The font size to update components with.
 */
- (void)setFontSizeForLabel:(CGFloat)fontSize;

/**
 * Updates all button components with the specified font size.
 *
 * @param fontSize The font size to update components with.
 */
- (void)setFontSizeForButton:(CGFloat)fontSize;

/**
 * Updates all label components with the specified font color.
 *
 * @param textColor The font size to update components with.
 */
- (void)setTextColorForLabel:(UIColor *)textColor;

/**
 * Updates all button components with the specified color for state.
 *
 * @param titleColor The color of the title to set.
 * @param state Controls state to set.
 */
- (void)setTitleColorForButton:(UIColor *)titleColor forState:(UIControlState)state;

/**
 * Returns an array of control components for the specified elements.
 *
 * @param basicComponents The components to return. Use bitwise
 * OR to specify multiple components.
 *
 * @return Array of UI componenets.
 */
+ (NSArray *)componentItemForBasicComponents:(BCOVPUIBasicComponents)basicComponents;

/**
 * Constructs the UI component with the specified tag. Default styles will
 * be applied.
 *
 * @param tag The tag to construct.
 *
 * @return Initialized UI component.
 */
+ (UIView *)createUIComponentItemWithViewTag:(BCOVPUIViewTag)tag;

/**
 * Returns the view tag for a given component.
 *
 * @param basicComponent Component whose tag to return.
 *
 * @return The tag for the specified component.
 */
+ (BCOVPUIViewTag)viewTagForBasicComponent:(BCOVPUIBasicComponents)basicComponent;

@end
