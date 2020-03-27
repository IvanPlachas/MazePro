uniform sampler2D u_texture;
uniform highp vec4 u_lightPosition;
uniform highp float u_lightPower;
uniform highp float u_specularFactor;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;
varying highp vec4 v_position;

void main(void)
{
    vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 diffMatColor = texture2D(u_texture, v_texcoord);
    vec3 eyeVect = normalize(v_position.xyz - eyePosition.xyz);
    vec3 lightVect = normalize(v_position.xyz - u_lightPosition.xyz);
    vec3 reflectLight = normalize(reflect(lightVect, v_normal));
    float len = length(v_position.xyz - eyePosition.xyz);
    float specularFactor = 900.0;
    float ambientFactor = 1.1;

    vec4 diffCollor = (diffMatColor * u_lightPower * max(0.0, dot(v_normal, -lightVect))) / (1.0 + 20.25 * pow(len, 2.0));
    resultColor += diffCollor;
    vec4 ambientColor = ambientFactor * diffCollor;
    resultColor += ambientColor;
    vec4 specularColor = u_specularFactor * vec4(1.0, 1.0, 1.0, 1.0) * u_lightPower * pow(max(0.0, dot(reflectLight, -eyeVect)), u_specularFactor)  / (100.0 + 0.25 * pow(len, 2.0)* u_specularFactor);
    resultColor += specularColor;

    gl_FragColor = resultColor;
}
