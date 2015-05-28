//
// BCOVPUICommon.h
// BCOVPUI
//
// Copyright (c) 2015 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <UIKit/UIKit.h>
#import <CoreMedia/CoreMedia.h>


/**
 * Tags for buttons used by various BCOV control elements.
 */
typedef NS_ENUM(NSInteger, BCOVPUIViewTag) {

    /** Tag for unknown button. */
    BCOVPUIViewTagUnknown,

    /**  Tag for playback button. */
    BCOVPUIViewTagButtonPlayback       = 1,

    /** Tag for jump back button. */
    BCOVPUIViewTagButtonJumpBack       = 2,

    /** Tag for closed caption button. */
    BCOVPUIViewTagButtonClosedCaption  = 3,

    /** Tag for the screen mode (fullscreen) button. */
    BCOVPUIViewTagButtonScreenMode     = 4,

    /** Tag for the current (elapsed time) label. */
    BCOVPUIViewTagLabelCurrentTime     = 5,

    /** Tag for the time separator label. */
    BCOVPUIViewTagLabelTimeSeparator   = 6,

    /** Tag for the duration label. */
    BCOVPUIViewTagLabelDuration        = 7,

    /** Tag for the progress slider. */
    BCOVPUIViewTagSliderProgress       = 8,

    /** Tag for the external route (airplay) button */
    BCOVPUIViewTagViewExternalRoute    = 9,

    /** Tag for the "go to live" button. */
    BCOVPUIViewTagViewLive             = 10,

    /** Tag that signifies the end of our reserved range. */
    BCOVPUIViewTagReservedEnd          = 200
};


/**
 * Type of video.
 */
typedef NS_ENUM(NSUInteger, BCOVPUIVideoType) {

    /** Video type can not be determined. */
    BCOVPUIVideoTypeUnknown,

    /** Video on demand (has a duration). */
    BCOVPUIVideoTypeVOD,

    /** Video has no duration, and a limited seekable range. */
    BCOVPUIVideoTypeLive,

    /** Video has no duration, and a large seekable range. */
    BCOVPUIVideoTypeLiveDVR
};


/**
 * Distinct Icon types.
 */
typedef NS_ENUM(NSUInteger, BCOVPUIButtonIcon) {

    /** Play icon. */
    BCOVPUIButtonIconPlay,

    /** Pause icon. */
    BCOVPUIButtonIconPause,

    /** Jump back icon. */
    BCOVPUIButtonIconJumpBack,

    /** Zoom in icon. */
    BCOVPUIButtonIconZoomIn,

    /** Zoom out icon. */
    BCOVPUIButtonIconZoomOut,

    /** Closed Caption icon. */
    BCOVPUIButtonIconClosedCaption,

    /** External Route (airplay) icon */
    BCOVPUIButtonIconExternalRoute,

    /** Reserved icon. */
    BCOVPUIButtonIconReserved,
};


@interface BCOVPUICommon : NSObject

/**
 * Icon font used by this plugin.
 */
+ (UIFont *)iconFont;

/**
 * Icon font used by this plugin at specified font size.
 *
 * @param fontSize Size of font to return.
 *
 * @return Font at specified size.
 */
+ (UIFont *)iconFontWithSize:(CGFloat)fontSize;

/**
 * Returns the unicode to be used with +iconFont or +iconFontWithSize:
 * for the given icon.
 *
 * @param buttonIcon The icon to return unicode for.
 *
 * @return Unicode string for the icon.
 */
+ (NSString *)fontUnicodeForButtonIcon:(BCOVPUIButtonIcon)buttonIcon;

/**
 * Color used by the Live label to indicate the stream is currently live.
 * Red:85.0/255.0 green:154.0/255.0 blue:66.0/255.0 alpha:1.0
 */
+ (UIColor *)liveViewTitleColorForLive;

/**
 * Color used by the progress slider maximum track tint.
 * Red:140.0/255.0 green:143.0/255.0 blue:140.0/255.0 alpha:1
 */
+ (UIColor *)progressSliderMaximumTrackTintColor;

/**
 * Color used by the progress slider minimum track tint.
 * Red:214.0/255.0 green:36.0/255.0 blue:133.0/255.0 alpha:1
 */
+ (UIColor *)progressSliderMinimumTrackTintColor;

/**
 * Color used by the progress slider buffered tint.
 * Red:255.0/255.0 green:255.0/255.0 blue:255.0/255.0 alpha:.8
 */
+ (UIColor *)progressSliderBufferProgressTintColor;

/**
 * Returns the default image for the volume view.
 *
 * @param fontSize The size of the font to create the image with.
 * @param color The color to use.
 *
 * @return The image.
 */
+ (UIImage *)imageForVolumeViewWithFontSize:(CGFloat)fontSize color:(UIColor *)color;

/**
 * Default font size used by labels.
 * 16.
 */
+ (CGFloat)defaultFontSizeForLabel;

/**
 * Default font size used by buttons.
 * 22.
 */
+ (CGFloat)defaultFontSizeForButton;

@end