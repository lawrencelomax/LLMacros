Pod::Spec.new do |s|
    s.name = 'LLMacros'
    s.version = '0.0.1'
    s.summary = 'A bunch of helpful macros.'
    s.license = {
      :type => 'MIT',
      :file => 'LICENSE'
    }
    s.source = { :git => 'https://github.com/lawrencelomax/LLMacros.git', :commit => 'HEAD' }
    s.author = 'Lawrence Lomax'
    s.homepage = 'https://github.com/lawrencelomax/LLMacros'
    s.platform = :ios, '4.3'
    s.source_files = 'LLMacros.h'
end